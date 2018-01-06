#ifndef DEFINES
#define DEFINES

#define TMMG_VERSION        "1.0.1"
#define MAX_NUM_PER_ROUND   50

//#define TEST_ON_MY_FORM
#ifdef TEST_ON_MY_FORM
    #define REQUESET_URL        "https://docs.google.com/forms/d/1HZUHpL-779nV2vbJ0dGELtmJdSeC0Ch2w8U6WRoS70M/formResponse"
    #define FIELD_NAME          "entry.907617469"
    #define FIELD_CITY          "entry.936986914"
    #define FIELD_AREA          "entry.1670000021"
    #define FIELD_CONTACT_CHK   "entry.1589837164"
    #define FIELD_HOMEPHONE     "entry.1857254885"
    #define FIELD_CELLPHONE     "entry.2009509130"
    #define FIELD_EMAIL         "entry.1430665122"
    #define FIELD_OTHER_PS      "entry.2047585356"
    #define FIELD_PAGE_HISTORY  "pageHistory"
#else
    #define REQUESET_URL        "https://docs.google.com/forms/d/xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
    #define FIELD_NAME          "entry.980124048"
    #define FIELD_CITY          "entry.1738810524"
    #define FIELD_AREA          "entry.1912815158"
    #define FIELD_CONTACT_CHK   "entry.292175519"
    #define FIELD_HOMEPHONE     "entry.1626986040"
    #define FIELD_CELLPHONE     "entry.170480013"
    #define FIELD_EMAIL         "entry.608572206"
    #define FIELD_OTHER_PS      "entry.837832613"
    #define FIELD_PAGE_HISTORY  "pageHistory"
#endif

#endif // DEFINES

