/*
 * SPDX-FileCopyrightText: 2016-2016 CSSlayer <wengxt@gmail.com>
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 *
 */
#ifndef _FCITX_TEXT_H_
#define _FCITX_TEXT_H_

#include <memory>
#include <string>
#include <fcitx-utils/flags.h>
#include <fcitx-utils/macros.h>
#include <fcitx-utils/textformatflags.h>
#include "fcitxcore_export.h"

/// \addtogroup FcitxCore
/// \{
/// \file
/// \brief Formatted string commonly used in user interface.

namespace fcitx {
class TextPrivate;

/// A class represents a formatted string.
class FCITXCORE_EXPORT Text {
public:
    Text();
    explicit Text(const std::string &text,
                  TextFormatFlags flag = TextFormatFlag::None);
    FCITX_DECLARE_VIRTUAL_DTOR_COPY_AND_MOVE(Text);

    /// Get cursor by byte.
    int cursor() const;
    /// Set cursor by byte.
    void setCursor(int pos = -1);
    void clear();
    void append(const std::string &str,
                TextFormatFlags flag = TextFormatFlag::None);
    const std::string &stringAt(int idx) const;
    TextFormatFlags formatAt(int idx) const;
    size_t size() const;
    size_t textLength() const;
    std::string toString() const;
    std::string toStringForCommit() const;

private:
    std::unique_ptr<TextPrivate> d_ptr;
    FCITX_DECLARE_PRIVATE(Text);
};
} // namespace fcitx

#endif // _FCITX_TEXT_H_
