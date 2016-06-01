#ifndef CONSTANTS_HPP_
# define CONSTANTS_HPP_

# define ERROR_CODE -1
# define OK_CODE 0

# if defined (_IRR_WINDOWS_) && ! defined (MSYS)
#  define ASSETS_DIR "../../assets"
# else
#  define ASSETS_DIR "./assets"
# endif

# define MAX_LIFE 100
# define NB_BONUS 2
# define HEAL_AMOUNT 10

#endif /* CONSTANTS_HPP_ */
