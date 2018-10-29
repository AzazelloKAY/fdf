cmake_minimum_required(VERSION 3.9)
project(fdf C)

set(CMAKE_C_STANDARD 99)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lmlx -lm -framework OpenGL -framework AppKit")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lmlx -lm -framework OpenGL -framework AppKit")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -framework OpenGL -framework AppKit")

add_executable(fdf
        fdffunctions.c   fdfmain.c        fdfmakeres.c     fdfperspective.c ft_brez.c
        fdfkeyhooks.c    fdfmakeimg.c     fdfparser.c      fdfrotation.c
        )

link_directories(libft)

target_link_libraries(fdf ${CMAKE_SOURCE_DIR}/libft/libft.a)