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
#pragma once

#include <memory>
#include <string>

#include "../Vq.h"
#include "../common/Macros.h"

namespace Vq { namespace Logger {

class AbstractLogTarget;
class LogMessage;
VQ_INTERFACE ILogFilter;

class VQ_API AbstractLogDispatcher
{
public:
    AbstractLogDispatcher();

    bool addTarget( std::unique_ptr< AbstractLogTarget > &&target );

    AbstractLogTarget * target( std::string targetId );

    bool setTargetEnabledState( const std::string &trgId, bool value );

    bool removeTarget( const std::string &targetId );

    bool installFilter( std::unique_ptr< ILogFilter > &&filter,
                        const std::string &trgtId );

    bool uninstallFilter( const std::string &filterId,
                          const std::string &trgtId );

    virtual void flush();

    virtual void write( LogMessage *message ) = 0;

    virtual void stopDispatch() = 0;

    virtual ~AbstractLogDispatcher();

protected:
    void writeToTargets( LogMessage *msg );

private:
    class Impl;
    std::unique_ptr< Impl > m_impl;

};

} } // end of namespaces

