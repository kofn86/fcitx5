/*
 * SPDX-FileCopyrightText: 2017-2017 CSSlayer <wengxt@gmail.com>
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 *
 */

#include "element.h"
#include <algorithm>
#include <unordered_map>
#include "misc_p.h"

namespace fcitx {

class ElementPrivate {
    typedef std::list<Element *> ElementList;

public:
    OrderedSet<Element *> parents_, childs_;
};

Element::Element() : d_ptr(std::make_unique<ElementPrivate>()) {}

Element::~Element() {
    removeAllParent();
    removeAllChild();
}

const std::list<Element *> &Element::childs() const {
    FCITX_D();
    return d->childs_.order();
}

void Element::addChild(Element *child) {
    addEdge(this, child, nullptr, nullptr);
}
void Element::addParent(Element *parent) {
    addEdge(parent, this, nullptr, nullptr);
}

bool Element::isChild(const Element *child) const {
    FCITX_D();
    return d->childs_.contains(const_cast<Element *>(child));
}
bool Element::isParent(const Element *parent) const {
    FCITX_D();
    return d->parents_.contains(const_cast<Element *>(parent));
}

const std::list<Element *> &Element::parents() const {
    FCITX_D();
    return d->parents_.order();
}

void Element::removeChild(Element *child) { removeEdge(this, child); }

void Element::removeParent(Element *parent) { removeEdge(parent, this); }

void Element::insertChild(Element *before, Element *child) {
    addEdge(this, child, before, nullptr);
}

void Element::insertParent(Element *before, Element *parent) {
    addEdge(parent, this, nullptr, before);
}

void Element::addEdge(Element *parent, Element *child, Element *beforeChild,
                      Element *beforeParent) {
    // Try not to invalidate the list iterator of elements.
    if (parent->d_func()->childs_.contains(child)) {
        return;
    }
    removeEdge(parent, child);
    parent->d_func()->childs_.insert(beforeChild, child);
    child->d_func()->parents_.insert(beforeParent, parent);
}

void Element::removeEdge(Element *parent, Element *child) {
    parent->d_func()->childs_.remove(child);
    child->d_func()->parents_.remove(parent);
}

void Element::removeAllParent() {
    while (parents().size()) {
        removeParent(parents().front());
    }
}

void Element::removeAllChild() {
    while (childs().size()) {
        childs().front()->removeParent(this);
    }
}
} // namespace fcitx
