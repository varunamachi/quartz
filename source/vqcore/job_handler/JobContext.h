#pragma once

#include <memory>
#include <functional>

namespace Vam {

class JobContext
{
public:
    using JobProgressCallback = std::function< void( int, int, int ) >;

    explicit JobContext( JobProgressCallback callback );

    bool cancelRequested() const;

    void requestCancel();

    void setProgress( int totalMilestones,
                      int milestonesCompleted,
                      int currentMilestoneProgress );

private:
    class Impl;
    std::unique_ptr< Impl > m_impl;
};

}
