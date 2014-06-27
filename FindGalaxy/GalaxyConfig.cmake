

SET(components std log network console)

IF(Galaxy_SHARED)
	SET(shared_postfix "_shared")
ENDIF()

MESSAGE(STATUS "FindGalaxy")

SET(pkg_name galaxy)

SET(${pkg_name}_LIBRARIES)

FOREACH(c ${Galaxy_FIND_COMPONENTS})
	
	LIST(FIND components "${c}" idx_${c})
	
	#MESSAGE(STATUS "idx_${c}: ${idx_${c}}")

	
	STRING(COMPARE EQUAL ${idx_${c}} "-1" not_${c})

	#MESSAGE(STATUS "not_${c}: ${not_${c}}")
	IF(${not_${c}})
		MESSAGE(ERROR "Component ${c} not found.")
	ELSEIF(NOT ${not_${c}})
		MESSAGE(STATUS "    ${c}")

		FIND_PACKAGE(${pkg_name}_${c}${shared_postfix})


		MESSAGE(STATUS "    libs: ${${pkg_name}_${c}_LIBRARIES}")
		
		
		SET(${pkg_name}_LIBRARIES
			${${pkg_name}_LIBRARIES}
			${${pkg_name}_${c}_LIBRARIES})

		
		
	ENDIF()
ENDFOREACH()




