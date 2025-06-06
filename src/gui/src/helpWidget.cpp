// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025, The OpenROAD Authors

#include "helpWidget.h"

#include <QFile>
#include <QHBoxLayout>
#include <QListWidgetItem>
#include <QTextStream>
#include <QVBoxLayout>
#include <filesystem>
#include <string>

namespace gui {

HelpWidget::HelpWidget(QWidget* parent)
    : QDockWidget("Help Browser", parent),
      category_selector_(new QComboBox(this)),
      help_list_(new QListWidget(this)),
      viewer_(new QTextBrowser(this))
{
  setObjectName("help_viewer");

  has_help_ = false;

  viewer_->setOpenExternalLinks(true);

  QHBoxLayout* layout = new QHBoxLayout;

  QVBoxLayout* select_layout = new QVBoxLayout;
  select_layout->addWidget(category_selector_);
  select_layout->addWidget(help_list_, /* stretch*/ 1);

  layout->addLayout(select_layout);
  layout->addWidget(viewer_, /* stretch*/ 1);

  QWidget* container = new QWidget(this);
  container->setLayout(layout);
  setWidget(container);

  // add connect
  connect(category_selector_,
          qOverload<int>(&QComboBox::currentIndexChanged),
          this,
          &HelpWidget::changeCategory);
  connect(help_list_,
          &QListWidget::currentItemChanged,
          this,
          &HelpWidget::showHelpInformation);
}

void HelpWidget::init(const std::string& path)
{
  has_help_ = false;
  category_selector_->clear();

  // validate path
  if (!std::filesystem::exists(path)) {
    return;
  }

  // check for html
  const std::filesystem::path html_path(std::filesystem::path(path) / "html");
  if (!std::filesystem::exists(html_path)) {
    return;
  }

  // add html1, html2, html3
  auto add_help = [this, &html_path](const std::string& category,
                                     const std::string& dir) {
    const std::filesystem::path doc_path(html_path / dir);
    if (std::filesystem::exists(doc_path)) {
      category_selector_->addItem(QString::fromStdString(category),
                                  QString::fromStdString(doc_path));
      has_help_ = true;
    }
  };

  add_help("application", "html1");
  add_help("commands", "html2");
  add_help("messages", "html3");

  if (hasHelp()) {
    category_selector_->setCurrentIndex(1);
  }
}

void HelpWidget::changeCategory()
{
  const std::filesystem::path dir(
      category_selector_->currentData().toString().toStdString());
  if (!std::filesystem::exists(dir)) {
    return;
  }

  help_list_->clear();

  for (auto const& dir_entry : std::filesystem::directory_iterator{dir}) {
    const auto& path = dir_entry.path();

    if (path.extension() != ".html") {
      continue;
    }

    auto* qitem = new QListWidgetItem(QString::fromStdString(path.stem()));
    qitem->setData(Qt::UserRole, QString::fromStdString(path));
    help_list_->addItem(qitem);
  }

  help_list_->sortItems();
}

void HelpWidget::showHelpInformation(QListWidgetItem* item)
{
  if (item == nullptr) {
    return;
  }
  const QString path = item->data(Qt::UserRole).toString();
  QFile html_file(path);
  if (html_file.open(QIODevice::ReadOnly)) {
    QTextStream in(&html_file);
    viewer_->setHtml(in.readAll());
  } else {
    viewer_->setHtml("Unable to open: " + path);
  }
}

void HelpWidget::selectHelp(const std::string& item)
{
  const int start_index = category_selector_->currentIndex();

  for (int i = 0; i < category_selector_->count(); i++) {
    category_selector_->setCurrentIndex(i);

    const auto help_items
        = help_list_->findItems(QString::fromStdString(item), Qt::MatchExactly);
    if (!help_items.empty()) {
      raise();
      show();

      help_list_->setCurrentItem(help_items[0]);
      return;
    }
  }

  category_selector_->setCurrentIndex(start_index);
}

}  // namespace gui
