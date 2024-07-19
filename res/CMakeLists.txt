
if(WIN32)
    install(FILES xpwm.desktop DESTINATION . COMPONENT desktop)
    install(FILES xpwm.png DESTINATION . COMPONENT desktop)
    install(FILES xpwm.ico DESTINATION . COMPONENT desktop)
else()
    install(FILES xpwm.desktop DESTINATION share/applications/ COMPONENT desktop)
    install(FILES xpwm.png DESTINATION share/icons/hicolor/256x256/apps COMPONENT desktop)
endif()