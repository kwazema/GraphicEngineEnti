
#include "../../Resource/Resource.h"
class Texture : public Resource
{
private:
	unsigned int texture;
public:
	virtual bool create(const std::string & file) override;

	inline unsigned int & getTexture()
	{
		return texture;
	}
};