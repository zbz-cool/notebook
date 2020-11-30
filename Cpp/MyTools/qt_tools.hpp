#ifndef QITAN_TOOLS_H
#define QITAN_TOOLS_H

#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <sstream>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <iomanip>
#include <iostream>
#define ACCESS access
#define MKDIR(a) (mkdir((a), 0755))

namespace qt_tools {

#ifdef __cplusplus
extern "C" {
#endif

static int lockfile(int fd) {
    struct flock fl;

    fl.l_type = F_WRLCK;
    fl.l_start = 0;
    fl.l_whence = SEEK_SET;
    fl.l_len = 0;

    return (fcntl(fd, F_SETLK, &fl));
}

/**************************************************************************************************
**  函数名称:  proc_is_exist
**  功能描述:  判断系统中是否存在该进程
**  输入参数:  procname: 进程名
**  输出参数:  无
**  返回参数:  返回1表示系统中已经存在该进程了；返回0表示系统中不存在该进程
**  注意事项:  此处加锁完后无需对文件进行close，而是进程退出后由系统来释放；否则无法起到保护的作用
**************************************************************************************************/
static int proc_is_exist(const char* procname) {
    int fd;
    char buf[16];
    char filename[100];

    sprintf(filename, "/var/tmp/%s.pid", procname);

    fd = open(filename, O_RDWR | O_CREAT, (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));
    if (fd < 0) {
        printf("open file \"%s\" failed!!!\n", filename);
        return 1;
    }

    if (lockfile(fd) == -1) { /* 尝试对文件进行加锁 */
        printf("file \"%s\" locked. proc already exit!!!\n", filename);
        close(fd);
        return 1;
    } else {
        ftruncate(fd, 0); /* 写入运行实例的pid */
        sprintf(buf, "%ld", (long)getpid());
        write(fd, buf, strlen(buf) + 1);
        return 0;
    }
}

#ifdef __cplusplus
}
#endif

/// <summary>
/// 分割字符串（忽略空行）
/// </summary>
/// <param name="str">原始字符串</param>
/// <param name="delims">分隔符，delims中的每一个字符都是分隔符</param>
/// <returns>分割后的字符串组</returns>
static std::vector<std::string> Split(const std::string& str, const std::string& delims) {
    std::vector<std::string> rtn;
    for (auto first = str.data(), second = str.data(), last = first + str.size(); second != last && first != last; first = second + 1) {
        second = find_first_of(first, last, delims.cbegin(), delims.cend());
        if (first != second)
            rtn.emplace_back(first, second);
    }
    return rtn;
}

/// <summary>
/// 分割字符串
/// </summary>
/// <param name="str">原始字符串</param>
/// <param name="delims">分隔符</param>
/// <param name="isSubStr">True: 将delims整体作为分隔符。 False:
/// delims中的每一个字符都是分隔符</param> <param name="saveNul">True:
/// 将保留空字符串</param> <returns>分割后的字符串组</returns>
static std::vector<std::string> Split(const std::string& str, const std::string& delims, bool isSubStr, bool saveNul = false) {
    std::vector<std::string> rtn;
    if (isSubStr) {
        for (auto first = str.data(), second = str.data(), last = first + str.size(); second != last && first != last; first = second + delims.size()) {
            auto it = str.find(delims, first - str.data());
            second = it == -1 ? last : &str[it];
            if (saveNul || first != second)
                rtn.emplace_back(first, second);
        }
    } else {
        for (auto first = str.data(), second = str.data(), last = first + str.size(); second != last && first != last; first = second + 1) {
            second = find_first_of(first, last, delims.cbegin(), delims.cend());
            if (saveNul || first != second)
                rtn.emplace_back(first, second);
        }
    }
    return rtn;
}

/// <summary>
/// 获取当前文件夹下所有文件名字
/// </summary>
/// <param name="path">文件夹路径</param>
/// <returns>包含的所有符合添加的文件的Vector列表</returns>
static std::vector<std::string> GetAllFileName(const std::string& path) {
    std::vector<std::string> files;
    DIR* open_dir = opendir(path.c_str());
    dirent* p = nullptr;
    while ((p = readdir(open_dir)) != nullptr) {
        struct stat st;
        if (p->d_name[0] != '.') {
            std::string name = path + '/' + std::string(p->d_name);
            stat(name.c_str(), &st);
            if (S_ISREG(st.st_mode)) {
                files.push_back(name);
            }
        }
    }
    closedir(open_dir);
    return files;
}

/// <summary>
/// 获取所有文件夹名字
/// </summary>
/// <param name="path">文件夹路径</param>
/// <returns>包含的所有文件夹名字的Vector列表</returns>
static std::vector<std::string> GetAllFolderName(const std::string& path) {
    char* pp;
    std::vector<std::string> rtn;
    DIR* dir = opendir(path.data());
    dirent* p = nullptr;
    struct stat statbuf;
    while ((p = readdir(dir)) != nullptr) {
        if (p->d_name[0] != '.') {
            std::string s = path + p->d_name;
            lstat(s.c_str(), &statbuf);
            if (S_ISDIR(statbuf.st_mode)) {
                rtn.emplace_back(p->d_name);
            }
        }
    }
    closedir(dir);
    return rtn;
}

static bool IsDir(const std::string& path) {
    if (path.empty()) {
        return false;
    }
    struct stat s;
    lstat(path.c_str(), &s);
    if (!S_ISDIR(s.st_mode)) {
        return false;
    }
    return true;
}

static bool IsFileExist(const std::string& file_path) {
    if (file_path.empty())
        return false;
    if (access(file_path.c_str(), F_OK) == 0)
        return true;
    return false;
}

inline static bool IsFileEmpty(const std::string& file) {
    struct stat s;
    lstat(file.c_str(), &s);
    return ((int)s.st_size == 0);
}

inline static bool DeleteFile(const std::string& path) {
    if (0 != access(path.c_str(), F_OK)) {
        return true;
    }
    remove(path.c_str());
    return true;
}

static bool IsH5File(const std::string& file_name) {
    const std::string h5_str = ".h5";
    const std::string fast5_str = ".fast5";

    if (file_name.size() > h5_str.size())
        if (file_name.find(h5_str) == file_name.size() - std::string(h5_str).size())
            return true;

    if (file_name.size() > fast5_str.size())
        if (file_name.find(fast5_str) == file_name.size() - std::string(fast5_str).size())
            return true;

    return false;
}

static std::string GetH5FileName(const std::string& tmp_path) {
    auto end_pos = tmp_path.find_last_of('.');
    auto start_pos = tmp_path.find_last_of('/');
    if (end_pos <= start_pos)
        return "";
    return tmp_path.substr(start_pos + 1, end_pos - start_pos - 1);
}

// 如果文件已经存在, 则不会再创建
static bool CreateFolder(const std::string& path) {
    if (NULL == opendir(path.c_str())) {
        mkdir(path.c_str(), 0775);
    }
    return true;
}

// 获取当前可执行程序的路径
static std::string GetCurrentDirectory() {
    std::string current_dir;
    current_dir.resize(PATH_MAX);
    int n = readlink("/proc/self/exe", &current_dir[0], PATH_MAX);
    current_dir.resize(n);
    return current_dir.substr(0, current_dir.rfind('/'));
}

static int CreateNewProcess(const std::string& process, char* const* args) {
    auto pid = fork();
    if (pid == 0) {
        auto rtn = execve(process.c_str(), args, nullptr);
        if (rtn != 0)
            return rtn;
        exit(EXIT_SUCCESS);  // exit child process
    }
    return pid;
}

inline static void _split(const std::string& s, char delim, std::vector<std::string>& elems) {
    std::stringstream ss(s);
    std::string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

inline static std::vector<std::string> Split(const std::string& s, char delim) {
    std::vector<std::string> elems;
    _split(s, delim, elems);
    return std::move(elems);
}

inline static std::string Execute(const std::string& cmd) {
    const uint32_t kBufLen = 3000;
    char buf_ps[kBufLen];
    std::string results;
    char tmp[kBufLen + 1];
    FILE* ptr;
    if ((ptr = popen(cmd.c_str(), "r")) != NULL) {
        while (fgets(buf_ps, kBufLen, ptr) != NULL) {
            memset(tmp, '\0', kBufLen + 1);
            memcpy(tmp, buf_ps, kBufLen);
            results += std::string(tmp);
        }
        pclose(ptr);
        ptr = NULL;
    } else {
        printf("popen %s error\n", cmd.c_str());
    }
    return results;
}

//模板函数：将string类型变量转换为常用的数值类型（此方法具有普遍适用性）
template <class Type>
inline static Type StringToNum(const std::string& str) {
    std::istringstream iss(str);
    Type num;
    iss >> num;
    return num;
}

template <typename T>
static std::string NumToString(T t) {
    std::ostringstream ss;
    ss << t;
    return ss.str();
}

inline static double Round(double t, int n) {
    double m = pow(10, n);
    return floor(t * m + 0.5) / m;  // floor 向下取整
}

template <typename T>
inline static T GetMiddle(const std::vector<T>& vec) {
    if (vec.empty())
        return 0;
    auto tmp_vec = vec;  // 不对输入数组做排序
    std::sort(tmp_vec.begin(), tmp_vec.end());
    auto len = tmp_vec.size();
    auto result = tmp_vec.at(len / 2);
    if (0 == len % 2) {
        result = (result + tmp_vec.at(len / 2 - 1)) / 2;
    }
    return result;
}

inline static uint64_t StandardTimeToStampTime(const std::string& datetime) {

    std::string format;
    if (datetime.find('T') != std::string::npos)
        format = "%Y-%m-%dT%H:%M:%S";
    else if (datetime.find('_') != std::string::npos)
        format = "%Y-%m-%d_%H:%M:%S";
    else if (datetime.find(' ') != std::string::npos)
        format = "%Y-%m-%d %H:%M:%S";
    struct tm* tmp_time = (struct tm*)malloc(sizeof(struct tm));
    auto tmp_list = Split(datetime, '.');
    int ms = 0;
    if (2 == tmp_list.size()) {
        ms = StringToNum<int>(tmp_list[1]);
    }
    strptime(tmp_list[0].c_str(), format.c_str(), tmp_time);
    auto result = mktime(tmp_time) * 1000 + ms;
    free(tmp_time);
    return result;
}

static int HMSToSeconds(const std::string& time) {
    auto tmp_list = Split(time, ':');
    if (3 != tmp_list.size())
        return 0;
    return StringToNum<int>(tmp_list[0]) * 3600 + StringToNum<int>(tmp_list[1]) * 60 + StringToNum<int>(tmp_list[2]);
}

template <typename T>
inline static void PrintVec(std::vector<T> tmp, std::string vec_name = "") {
    std::cout.setf(std::ios::left);
    std::cout << vec_name << " [ ";
    for (auto& t : tmp) {
        std::cout << t << " ";
    }
    std::cout << "]" << std::endl;
}

static std::string GetCurrentTimeAndDate() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    return ss.str();
}

static std::string GetCurrentDate() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d");
    return ss.str();
}

class GetRunTime {
public:
    GetRunTime() {
        begin_time_ = std::chrono::high_resolution_clock::now();
    }

    std::string Mark(const std::string& str = "") {
        std::ostringstream ss;
        auto endTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - begin_time_);
        ss << str << ((double)elapsedTime.count()) / 1000 << " ms";
        return ss.str();
    }

private:
    decltype(std::chrono::high_resolution_clock::now()) begin_time_;
};

/// <summary>
/// 循环创建需要的文件夹
/// </summary>
/// <param name="path">完整的文件夹路径</param>
static void CreatNewFloder(const std::string path) {
    if (ACCESS(path.data(), 0) != 0) {
        size_t off = 0;
        while (true) {
            off = path.find_first_of("\\/", off);
            if (off == -1)
                break;
            auto subs = path.substr(0, off++);
            if (ACCESS(subs.data(), 0) != 0)
                MKDIR(path.data());
        }
    }
}

/// <summary>
/// 文件路径分隔符归一化
/// </summary>
/// <param name="path">文件路径,原地改变</param>
/// <param name="sign">需要归一化后的符号，默认'/',只能是'/'或者'\\'</param>
/// <returns>是否归一化成功</returns>
static bool PathSignNormal(std::string& path, char sign = '/') {
    if (sign == '/')
        std::replace(path.begin(), path.end(), '\\', '/');
    else if (sign == '\\')
        std::replace(path.begin(), path.end(), '/', '\\');
    else
        return false;
    return true;
}
}  // namespace qt_tools

#endif