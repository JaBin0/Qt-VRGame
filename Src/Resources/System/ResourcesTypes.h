#ifndef RESOURCESTYPES_H
#define RESOURCESTYPES_H
// Qt headers
#include <QMap>
#include <QString>

// ========== DAE FILE TYPE ==========
class DAE {
public:
    // Tags name
    enum TAG {
        INVALID_TAG = 0,
        ASSET,
        LIB_IMAGES,
        LIB_EFFECTS,
        LIB_MATERIALS,
        LIB_GEOMETRIC,
        LIB_CONTROLLERS,
        LIB_VISUAL_SCENES,
        SCNENE,
    };

    // Dictionary which convert string representation of the dae tag, to its numerate format
    static const QMap<QString, TAG> TAG_ID;
};

const QMap<QString, DAE::TAG> DAE::TAG_ID  = {
    {"asset",                 DAE::TAG::ASSET},
    {"scene",                 DAE::TAG::SCNENE},
    {"library_images",        DAE::TAG::LIB_IMAGES},
    {"library_effects",       DAE::TAG::LIB_EFFECTS},
    {"library_materials",     DAE::TAG::LIB_MATERIALS},
    {"library_geometries",    DAE::TAG::LIB_GEOMETRIC},
    {"library_controllers",   DAE::TAG::LIB_CONTROLLERS},
    {"library_visual_scenes", DAE::TAG::LIB_VISUAL_SCENES},
};

// ========== OBJ FILE TYPE ==========

#endif // RESOURCESTYPES_H
