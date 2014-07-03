

SET(components core gfx physx final python)
SET(pkg_name Nebula)


STRING(TOLOWER ${pkg_name} pkg_name_lower)


IF(${pkg_name_lower}_SHARED)
	SET(shared_postfix "_shared")
ENDIF()

MESSAGE(STATUS "Find ${pkg_name}")

FOREACH(c ${components})

	LIST(FIND ${pkg_name}_FIND_COMPONENTS "${c}" idx_${c})
	
	#MESSAGE(STATUS "idx_${c}: ${idx_${c}}")
	
	
	STRING(COMPARE EQUAL ${idx_${c}} "-1" not_${c})
	
	#MESSAGE(STATUS "not_${c}: ${not_${c}}")
	
	IF(NOT ${not_${c}})
		MESSAGE(STATUS "    ${c}")
		FIND_PACKAGE(${pkg_name_lower}_${c}${shared_postfix})



		SET(
			${pkg_name}_LIBRARIES
			${${pkg_name}_LIBRARIES}
			${${pkg_name_lower}_${c}_LIBRARIES})

	ENDIF()
	
	MESSAGE(STATUS "${pkg_name}_LIBRARIES ${${pkg_name}_LIBRARIES}")	

ENDFOREACH()





