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

#include "ILogDispatcher.h"
#include "../VQ.h"

namespace Vam { namespace Logger {

struct FilterInfo;
struct TargetInfo;

class VQ_CORE_EXPORT AbstractLogDispatcher : public ILogDispatcher
{
public:
    AbstractLogDispatcher();

    bool addTarget( std::shared_ptr< AbstractLogTarget > target );

    AbstractLogTarget * target( QString targetId );

    bool setTargetEnabledState( const QString &trgId, bool value );

    bool removeTarget( const QString &targetId );

    bool installFilter( std::shared_ptr< ILogFilter > filter,
                        const QString &trgtId );

    bool uninstallFilter( const QString &filterId,
                          const QString &trgtId );

    void flush();

    ~AbstractLogDispatcher();

protected:
    void writeToTargets( LogMessage *msg );

private:
    class Impl;
    std::unique_ptr< Impl > m_impl;

};

} } // end of namespaces

