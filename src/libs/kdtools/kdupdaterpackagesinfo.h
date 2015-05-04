/****************************************************************************
**
** Copyright (C) 2013 Klaralvdalens Datakonsult AB (KDAB)
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Installer Framework.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef KD_UPDATER_PACKAGES_INFO_H
#define KD_UPDATER_PACKAGES_INFO_H

#include "kdupdater.h"

#include <QCoreApplication>
#include <QDate>
#include <QVariant>

namespace KDUpdater {

struct KDTOOLS_EXPORT PackageInfo
{
    QString name;
    QString pixmap;
    QString title;
    QString description;
    QString version;
    QString inheritVersionFrom;
    QStringList dependencies;
    QStringList translations;
    QDate lastUpdateDate;
    QDate installDate;
    bool forcedInstallation;
    bool virtualComp;
    quint64 uncompressedSize;
};

class KDTOOLS_EXPORT PackagesInfo
{
    Q_DISABLE_COPY(PackagesInfo)
    Q_DECLARE_TR_FUNCTIONS(PackagesInfo)

public:
    PackagesInfo();
    ~PackagesInfo();

    enum Error
    {
        NoError = 0,
        NotYetReadError,
        CouldNotReadPackageFileError,
        InvalidXmlError,
        InvalidContentError
    };

    bool isValid() const;
    QString errorString() const;
    Error error() const;
    void clearPackageInfoList();

    void setFileName(const QString &fileName);
    QString fileName() const;

    void setApplicationName(const QString &name);
    QString applicationName() const;

    void setApplicationVersion(const QString &version);
    QString applicationVersion() const;

    int packageInfoCount() const;
    PackageInfo packageInfo(int index) const;
    int findPackageInfo(const QString &pkgName) const;
    QVector<KDUpdater::PackageInfo> packageInfos() const;
    void writeToDisk();

    bool installPackage(const QString &pkgName, const QString &version, const QString &title = QString(),
                        const QString &description = QString(), const QStringList &dependencies = QStringList(),
                        bool forcedInstallation = false, bool virtualComp = false, quint64 uncompressedSize = 0,
                        const QString &inheritVersionFrom = QString());

    bool updatePackage(const QString &pkgName, const QString &version, const QDate &date);
    bool removePackage(const QString &pkgName);

    void refresh();

private:
    struct PackagesInfoData;
    PackagesInfoData *d;
};

} // KDUpdater

#endif // KD_UPDATER_PACKAGES_INFO_H
