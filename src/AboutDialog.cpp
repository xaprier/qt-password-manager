#include "AboutDialog.hpp"

#include "Config.hpp"

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent), m_ui(new Ui::AboutDialog) {
    m_ui->setupUi(this);
#if QT_VERSION < QT_VERSION_CHECK(6, 1, 0)
    QDialog::setWindowIcon(QIcon(":/icons/XPwm.png"));
#endif
    QStringList list;

    // filling textbrowser
    QString sText = "<p align=\"center\"><br />\n";
    sText += "<b><big>" PROJECT_NAME "</big></b><br />\n";
    sText += tr(PROJECT_DESCRIPTION) + "<br />\n";
    sText += "<br />\n";
    sText += tr("Project Version") + ": <b>" PROJECT_VERSION "</b>, ";
    sText += tr("Using: Qt <b>%1</b>").arg(qVersion());
    if (!list.isEmpty()) {
        sText += "<small><font color=\"red\">";
        sText += list.join("<br />\n");
        sText += "</font></small>";
    }
    sText += "<br />\n";
    sText += "<br />\n";
    sText += tr("Website") + ": <a href=\"" PROJECT_HOMEPAGE_URL "\">" PROJECT_HOMEPAGE_URL "</a><br />\n";
    sText += "<br />\n";
    sText += tr("Organization") + ": " PROJECT_ORGANIZATION "<br />\n";
    sText += "<br />\n";
    sText += "<small>";
    sText += "<br />\n";
    sText += tr("This program is free software; you can redistribute it and/or modify it") + "<br />\n";
    sText += tr("under the terms of the GNU General Public License version 3 or later.");
    sText += "</small>";
    sText += "</p>\n";
    m_ui->aboutTextBrowser->setText(sText);
}

AboutDialog::~AboutDialog() {
    delete m_ui;
}
