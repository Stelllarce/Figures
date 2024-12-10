add_executable(app)

set_target_properties(app PROPERTIES OUTPUT_NAME "app")

target_link_libraries(
	app
	PRIVATE
		figurelib
)

target_sources(
	app
	PRIVATE
		"application.cpp"
)