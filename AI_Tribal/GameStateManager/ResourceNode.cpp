#include "ResourceNode.h"
ResourceNode::ResourceNode()
{

}
ResourceNode::~ResourceNode()
{

}

void ResourceNode::SetResource1(int amount)
{
	m_resource1 = amount;
}
void ResourceNode::SetResource2(int amount)
{
	m_resource2 = amount;
}
void ResourceNode::GiveResource1(int amount)
{
	m_resource1 -= amount;
}
void ResourceNode::GiveResource2(int amount)
{
	m_resource2 -= amount;
}