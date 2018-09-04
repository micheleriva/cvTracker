#ifndef CVTRACKER_CONSTANTS_H
#define CVTRACKER_CONSTANTS_H

namespace window {
    const std::string kTracker = "Target";
}

namespace source {
    enum type {
        image,
        video,
        camera
    };
}

namespace tracker {
    enum type {
        mil,
        boosting
    };

    static const char * TrackerValues[] = { "MIL", "BOOSTING" };
    inline const char * getCharForEnum(int enumVal) {
        return TrackerValues[enumVal];
    }
}


#endif //CVTRACKER_CONSTANTS_H