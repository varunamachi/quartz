/*******************************************************************************
 * Copyright (c) 2014 Varuna L Amachi. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 ******************************************************************************/

#include "Logger.h"
#include "LogStructures.h"
#include "AbstractLogDispatcher.h"
#include "LogMessage.h"


namespace Quartz { namespace Logger {

QZ_INTERFACE ILogDispatcher;


class Logger::Impl
{
public:

    inline void setDispatcher(
            std::unique_ptr<AbstractLogDispatcher> &&dispatcher)
    {
        m_dispatcher = std::move(dispatcher);
    }

    inline AbstractLogDispatcher * dispatcher() const
    {
        return m_dispatcher.get();
    }

    inline void setFilterLevel(LogLevel level)
    {
        m_globalSevLevel = level;
    }

    inline bool isMethodLoggingEnabled() const
    {
        return m_logMethods;
    }

    inline void setMethodLogState(bool value)
    {
        m_logMethods = value;
    }

    inline LogLevel filterLevel() const
    {
        return m_globalSevLevel;
    }

    inline bool isEnabled() const
    {
        return m_enabled;
    }

    inline void setEnabled(bool val)
    {
        m_enabled = val;
    }

    void log(LogMessage *msg);

    Impl(std::unique_ptr<AbstractLogDispatcher> dispatcher,
          LogLevel level)
        : m_dispatcher(std::move(dispatcher))
        , m_globalSevLevel(level)
        , m_logMethods(false)
        , m_enabled(true)
    {

    }

private:
    std::unique_ptr<AbstractLogDispatcher> m_dispatcher;

    LogLevel m_globalSevLevel;

    bool m_logMethods;

    bool m_enabled;

};


void Logger::Impl::log(LogMessage *msg)
{
    if (m_enabled
        && m_dispatcher != nullptr
        && msg->logLevel() >= m_globalSevLevel) {
        m_dispatcher->write(msg);
    }
}


//=================================VQLogger ===================================

std::unique_ptr<Logger> Logger::s_instance = nullptr;



void Logger::setDispatcher(
        std::unique_ptr<AbstractLogDispatcher> &&dispatcher)
{
    m_impl->setDispatcher(std::move(dispatcher));
}


AbstractLogDispatcher * Logger::dispatcher() const
{
    return m_impl->dispatcher();
}


LogLevel Logger::filterLevel() const
{
    return m_impl->filterLevel();
}


void Logger::setFilterLevel(LogLevel level)
{
    m_impl->setFilterLevel(level);
}


bool Logger::isMethodLoggingEnabled() const
{
    return m_impl->isMethodLoggingEnabled();
}

void Logger::setMethodLogState(bool value)
{
    m_impl->setMethodLogState(value);
}



bool Logger::isEnabled() const
{
    return m_impl->isEnabled();
}


void Logger::setEnabled(bool val)
{
    m_impl->setEnabled(val);
}



bool Logger::init(std::unique_ptr <AbstractLogDispatcher> &&dispatcher,
                     LogLevel level)
{
    bool result = false;
    if (s_instance == nullptr) {
//        s_instance = std::make_unique<VqLogger>(std::move(dispatcher),
//                                                   level);
        s_instance = std::unique_ptr<Logger>{
                new Logger(std::move(dispatcher), level)};
        result = true;
    }
    return result;
}


void Logger::destroy()
{
    s_instance.release();
}


void Logger::log(LogMessage *msg)
{
    m_impl->log(msg);
}


Logger::Logger(std::unique_ptr<AbstractLogDispatcher> dispatcher,
                    LogLevel level)
//    : m_impl(std::make_unique<Impl>(std::move(dispatcher), level))
    : m_impl(new Impl(std::move(dispatcher), level))
{

}


Logger * Logger::get()
{
    return s_instance.get();
}

} } // end of namespaces
