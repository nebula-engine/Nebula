

SET(components std log network console)

IF(Galaxy_SHARED)
	SET(shared_postfix "_shared")
ENDIF()

MESSAGE(STATUS "FindGalaxy")

FOREACH(c ${components})

	LIST(FIND Galaxy_FIND_COMPONENTS "${c}" idx_${c})
	
	#MESSAGE(STATUS "idx_${c}: ${idx_${c}}")

	
	STRING(COMPARE EQUAL ${idx_${c}} "-1" not_${c})

	#MESSAGE(STATUS "not_${c}: ${not_${c}}")
		
	IF(NOT ${not_${c}})
		MESSAGE(STATUS "    ${c}")
		FIND_PACKAGE(galaxy_${c}${shared_postfix})
	ENDIF()
ENDFOREACH()





