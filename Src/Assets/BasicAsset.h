#ifndef BASICASSET_H
#define BASICASSET_H
// Qt headers
#include <QMatrix4x4>

// Own headers
#include <AssetTypes.h>

class BasicAsset
{
public:
    // Constructors && Destructor
    BasicAsset(const ASSET_TYPES type);
    BasicAsset(const ASSET_TYPES type, const QVector3D positon);

    // Return type o the asset
    ASSET_TYPES type() const;

    // Return transformation of Asset
    QMatrix4x4 transformation() const;

protected:
    // Type o the asset
    ASSET_TYPES m_type;

    // State of the asset in the scence
    QMatrix4x4 m_transformation;
};

#endif // BASICASSET_H
