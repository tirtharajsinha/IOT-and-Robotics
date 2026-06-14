#pragma once

#include "Match.h"

class ApiClient
{
public:

    bool fetchFixtures(
        Match* matches,
        int& count
    );

private:

    bool requestFixtures(
        String& response
    );

    bool parseFixtures(
        const String& json,
        Match* matches,
        int& count
    );
    
};

extern ApiClient Api;