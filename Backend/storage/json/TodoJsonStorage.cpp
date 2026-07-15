#include "TodoJsonStorage.hpp"

StorageResult TodoJsonStorage::load(QList<Task_t> &tasks)
{
    if (!m_file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug() << "Failed to open file:" << m_file.errorString();
        return StorageResult{StorageError::OpenFailed, m_file.errorString()};
    }
    QByteArray data = m_file.readAll();
    if (data.trimmed().isEmpty())
    {
        m_file.resize(0);
        // TODO
    }
    return false;
}
