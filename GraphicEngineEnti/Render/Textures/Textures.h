
#include "../../Resource/Resource.h"
class Texture : public Resource
{
	virtual bool create(const std::string & file) override;
};