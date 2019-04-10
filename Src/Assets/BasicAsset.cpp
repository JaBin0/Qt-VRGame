#include <BasicAsset.h>

BasicAsset::BasicAsset(const ASSET_TYPES type)
    : m_type{type}
    , m_transformation{}
{

}

BasicAsset::BasicAsset(const ASSET_TYPES type, const QVector3D position)
    : BasicAsset(type)
{
    m_transformation.translate(position);
}

ASSET_TYPES BasicAsset::type() const {
    return m_type;
}

QMatrix4x4 BasicAsset::transformation() const
{
    return m_transformation;
}
