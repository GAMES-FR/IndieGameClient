#ifndef CONSTANTS_HPP_
# define CONSTANTS_HPP_

# define ERROR_CODE -1
# define OK_CODE 0

# if defined (_IRR_WINDOWS_) && ! defined (MSYS)
#  define ASSETS_DIR "../../assets"
# else
#  define ASSETS_DIR "./assets"
# endif

# define MISSILE_MESH_PATH ASSETS_DIR"/bear.obj"
# define SPAWNER_MESH_PATH ASSETS_DIR"/bear.obj"

#endif /* CONSTANTS_HPP_ */
