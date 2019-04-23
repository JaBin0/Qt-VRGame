#ifndef ASSETSID_H
#define ASSETSID_H
// Qt headers
#include <QMap>


class Asset {
public:
    // Id of asset models types
    enum MODEL_ID {
        INVALID_ID = 0,
        GROUND,
        ASSETID_COUNT,
    };

    // Return model ID based on the given name
    static MODEL_ID str_to_modelId(QString name);

    static QString modelId_to_str(MODEL_ID id);

private:
    static QMap<QString, Asset::MODEL_ID> m_assetModelIdDictionary;
};
#endif // ASSETSID_H

