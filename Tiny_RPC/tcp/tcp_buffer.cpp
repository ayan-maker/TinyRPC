#include "tcp_buffer.h"
#include <string.h>


Tcp_buffer::Tcp_buffer(int size) : m_size(size) {
    m_read_pos = 0;
    m_write_pos = 0;
}

Tcp_buffer::~Tcp_buffer() {

}

int Tcp_buffer::get_size() {
    return m_size;
}

int Tcp_buffer::get_read_pos() {
    return m_read_pos;
}

int Tcp_buffer::get_write_pos() {
    return m_write_pos;
}

void Tcp_buffer::read_to_buffer(char *buffer, int size) {
    // 超过上限了
    while(size + m_read_pos > m_size) {
        change_size(2*m_size);
    }
    memcpy(&m_buffer[m_read_pos],buffer,size);
    m_read_pos = m_read_pos + size;
}

void Tcp_buffer::write_from_buffer(char *buffer, int size) {
    buffer = &m_buffer[m_write_pos];
    m_write_pos = m_write_pos + size;
}

void Tcp_buffer::change_size(int size) {
    std::vector<char> tmp(size,0);
    int t = std::min(size,m_read_pos);
    memcpy(&tmp,&m_buffer,t);
    
    m_buffer.swap(tmp);
    m_size = size;
    m_read_pos = std::min(size,m_read_pos);
}