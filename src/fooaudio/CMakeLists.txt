set( fooaudio_SRCS
    abstractaudioplugin.cpp
    fooabout.cpp
    fooaudio.cpp
    fooaudioengine.cpp
    fooaudioengineplugin.cpp
    foochangename.cpp
    foomainwindow.cpp
    fooplaylistwidget.cpp
    footabbar.cpp
    footabwidget.cpp
    footracklist.cpp
    footrack.cpp
    fooapplication.cpp
    tracklistmodel.cpp
    logic/applicationlogic.cpp
)

set( fooaudio_MOC
    #abstractaudiointerface.h
    abstractaudioplugin.h
    fooabout.hpp
    fooaudioengine.hpp
    fooaudioengineplugin.hpp
    foochangename.hpp
    foomainwindow.hpp
    #fooplaylistwidget.hpp
    footabbar.hpp
    footabwidget.hpp
    #footrack.hpp
    #footracklist.hpp
    fooapplication.h
    tracklistmodel.hpp
    logic/applicationlogic.h
)

qt4_wrap_cpp(fooaudio_MOCS ${fooaudio_MOC})
qt4_add_resources( fooaudio_SRCS resource.qrc )

add_executable( fooaudio ${fooaudio_SRCS} ${fooaudio_MOCS})

add_dependencies(fooaudio ${QT_LIBRARIES} ${QT_PHONON_LIBRARY})

target_link_libraries(fooaudio ${QT_LIBRARIES} ${QT_PHONON_LIBRARY} )

######### install ####################################################

#install(TARGETS xx  ${INSTALL_TARGETS_DEFAULT_ARGS} )
#install( FILES x.x  DESTINATION  ${KCFG_INSTALL_DIR} )
#install( FILES x.y  DESTINATION  ${DATA_INSTALL_DIR}/fooaudio )

