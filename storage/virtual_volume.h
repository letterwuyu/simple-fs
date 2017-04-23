#ifndef VIRTUAL_VOLUME_H
#define VIRTUAL_VOLUME_H
#include <map>
#include "volume.h"
#include "session.h"
class VirtualVolume {
private:
	std::map<Session, Volume> volumes;	
};
#endif /* VIRTUAL_VOLUME_H */
