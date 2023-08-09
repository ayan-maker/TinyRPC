/*
* 加码解码基类
*/

#ifndef _ABSTRACTCODEC_H_
#define _ABSTRACTCODEC_H_

#include <memory>

class AbstractCodeC {
public:
    std::shared_ptr<AbstractCodeC> Ptr;

    AbstractCodeC() {}

    virtual ~AbstractCodeC() {}

    virtual void encode() = 0;

    virtual void decode() = 0;
private:


};


#endif