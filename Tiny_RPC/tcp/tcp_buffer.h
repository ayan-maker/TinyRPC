/**
 * tcp 的缓冲区 用于存放tcp的接受文件或者发生的文件
*/

#ifndef _TCP_BUFFER_H_
#define _TCP_BUFFER_H_

#include <vector>


class Tcp_buffer {
public:

    Tcp_buffer(int size);

    ~Tcp_buffer();

    int get_size();

    int get_read_pos();

    int get_write_pos();

    void read_to_buffer(char *buffer, int size);

    void write_from_buffer(char *buffer, int size);

private:
    void change_size(int size);
    
    std::vector<char> m_buffer;
    int m_size;
    int m_read_pos; // 用于read时记录读操作每步结束后的位置方便下次读入
    int m_write_pos; // 写操作是方便连接写到了那里

};

#endif