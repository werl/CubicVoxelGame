//
// Created by Peter Lewis on 2017-11-19.
//

#ifndef CUBICVOXELGAME_TIME_MANAGER_HPP
#define CUBICVOXELGAME_TIME_MANAGER_HPP

namespace transport {
    class TimeManager {
    private:
        TimeManager();
    public:

        TimeManager(TimeManager const&) = delete;
        TimeManager& operator=(TimeManager const&) = delete;

        static TimeManager* INSTANCE();
        double getDeltaTime();
        void beginFrame();
    };
}

#endif //CUBICVOXELGAME_TIME_MANAGER_HPP
