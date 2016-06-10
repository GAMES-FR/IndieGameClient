#ifndef CONSTANTS_HPP_
# define CONSTANTS_HPP_

# define ERROR_CODE -1
# define OK_CODE 0

# if defined (_IRR_WINDOWS_) && ! defined (MSYS)
#  define ASSETS_DIR "../../assets/"
# else
#  define ASSETS_DIR "./assets"
# endif

# define MAP_MESH_PATH		ASSETS_DIR"mp/arena2.obj"
# define CAR_MESH_PATH		ASSETS_DIR"tcar/f.obj"
# define ENEMY_MESH_PATH	ASSETS_DIR"truck/camion.obj"

# define MISSILE_MESH_PATH	ASSETS_DIR"missils/missils.obj"	
# define MISSILE_SCALE		1.f

# define SPAWNER_MESH_PATH	ASSETS_DIR"bear.obj"

#endif /* CONSTANTS_HPP_ */
