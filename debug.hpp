#include <stdio.h>

#ifndef DEBUG_HPP
#define DEBUG_HPP
#define DEBUG 1


#define debug_printf(fmt, ...) \
	do { if (DEBUG) { \
		fprintf(stderr, fmt, ##__VA_ARGS__); \
		fflush(stderr); } } while (0)

#define ASSERT_EX(condition, statement) \
    do { \
        if (!(condition)) { std::cout<<__FILE__<<":"<<__LINE__<<":Assert message:"; statement; assert(condition); } \
    } while (false)
//#define ASSERT_EX(condition, statement) ((void)0)
//----------------------------------------------
#ifndef NDEBUG

//------------------------------Marzie's debug functions

//#define ALWAYS_WAIT_FOR_TRACKING

#ifndef ALWAYS_WAIT_FOR_TRACKING
#define TRACK_PRINTING(condition, statement) \
	    do { \
	        if ((condition)) { std::cout<<__FILE__<<":"<<__LINE__<<":Tracking message:";statement; } \
	    } while (false)
#else
#define TRACK_PRINTING(condition, statement) \
		do { \
			char charTowait;\
			if ((condition)) { std::cout<<__FILE__<<":"<<__LINE__<<":Tracking message:";statement;std::cout<<"press any character ...";std::cin>>charTowait; } \
		} while (false)
#endif
//----------------------------------------------
#define TRACK_And_WAIT_PRINTING(conditionTracking, conditionWaiting, statement) \
	    do { \
	    	char charTowait;\
	        if ((conditionTracking)) { std::cout<<__FILE__<<":"<<__LINE__<<":Tracking message:";statement;std::cout<<"press any character ...";if(conditionWaiting){std::cin>>charTowait;} } \
	    } while (false)
//----------------------------------------------

#else

#define TRACK_PRINTING(condition, statement) ((void)0)
#define TRACK_And_WAIT_PRINTING(conditionTracking, conditionWaiting, statement) ((void)0)
#endif



#endif   //End of file
