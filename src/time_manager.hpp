//
// Created by Peter Lewis on 2017-11-19.
//

#ifndef TRANSPORTCONCEPT2D_TIME_MANAGER_HPP
#define TRANSPORTCONCEPT2D_TIME_MANAGER_HPP

#include <memory>

namespace transport {
    class TimeManager {
    private:
        TimeManager();
    public:

        TimeManager(TimeManager const&) = delete;
        TimeManager& operator=(TimeManager const&) = delete;

        static std::shared_ptr<TimeManager> instance()
        {
            static std::shared_ptr<TimeManager> s{new TimeManager};
            return s;
        }
        static TimeManager* INSTANCE();
        double getDeltaTime();
        void beginFrame();
    };
}

#endif //TRANSPORTCONCEPT2D_TIME_MANAGER_HPP
