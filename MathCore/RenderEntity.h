#pragma once

class RenderEntity
{
public:
	virtual ~RenderEntity() = default;
	virtual void render() = 0;
};

