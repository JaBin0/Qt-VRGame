#include <Asset.h>

QMap<QString, Asset::MODEL_ID> Asset::m_assetModelIdDictionary = {
    {"Ground", MODEL_ID::GROUND},
};

Asset::MODEL_ID Asset::str_to_modelId(QString name) {
    return m_assetModelIdDictionary.value(name);
}

QString Asset::modelId_to_str(Asset::MODEL_ID id)
{
    return m_assetModelIdDictionary.key(id);
}
