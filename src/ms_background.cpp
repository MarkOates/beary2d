#include <beary2d/ms_background.h>





bool ms_background_sort_func(const MSBackground *b1, const MSBackground *b2)
{
	return b1->z_index < b2->z_index;
}


