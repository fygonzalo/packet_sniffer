# Find Detours
# Detours_FOUND - system has the Detours library
# Detours_INCLUDE_DIRS - the Detours include directory
# Detours_LIBRARIES - The libraries needed to use Detours

if (Detours_INCLUDE_DIRS AND Detours_LIBRARIES)
	# in cache already
	SET(Detours_FOUND TRUE)
else (Detours_INCLUDE_DIRS AND Detours_LIBRARIES)
	FIND_PATH(Detours_INCLUDE_DIRS NAMES detours.h PATH_SUFFIXES include)

	FIND_LIBRARY(Detours_LIBRARIES NAMES detours.lib PATH_SUFFIXES lib.X86)

	if (Detours_INCLUDE_DIRS AND Detours_LIBRARIES)
		 set(Detours_FOUND TRUE)
	endif (Detours_INCLUDE_DIRS AND Detours_LIBRARIES)

	if (Detours_FOUND)
		 if (NOT Detours_FIND_QUIETLY)
				message(STATUS "Found Detours: ${Detours_LIBRARIES}")
		 endif (NOT Detours_FIND_QUIETLY)
	else (Detours_FOUND)
		 if (Detours_FIND_REQUIRED)
				message(FATAL_ERROR "Could NOT find Detours")
		 endif (Detours_FIND_REQUIRED)
	endif (Detours_FOUND)

	MARK_AS_ADVANCED(Detours_INCLUDE_DIRS Detours_LIBRARIES)
endif (Detours_INCLUDE_DIRS AND Detours_LIBRARIES)