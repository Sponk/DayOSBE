
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __javax_swing_JTabbedPane__
#define __javax_swing_JTabbedPane__

#pragma interface

#include <javax/swing/JComponent.h>
#include <gcj/array.h>

extern "Java"
{
  namespace java
  {
    namespace awt
    {
        class Color;
        class Component;
        class Rectangle;
      namespace event
      {
          class MouseEvent;
      }
    }
  }
  namespace javax
  {
    namespace accessibility
    {
        class AccessibleContext;
    }
    namespace swing
    {
        class Icon;
        class JTabbedPane;
        class SingleSelectionModel;
      namespace event
      {
          class ChangeEvent;
          class ChangeListener;
      }
      namespace plaf
      {
          class TabbedPaneUI;
      }
    }
  }
}

class javax::swing::JTabbedPane : public ::javax::swing::JComponent
{

public:
  JTabbedPane();
  JTabbedPane(jint);
  JTabbedPane(jint, jint);
  virtual ::javax::swing::plaf::TabbedPaneUI * getUI();
  virtual void setUI(::javax::swing::plaf::TabbedPaneUI *);
  virtual void updateUI();
  virtual ::java::lang::String * getUIClassID();
public: // actually protected
  virtual ::javax::swing::event::ChangeListener * createChangeListener();
public:
  virtual void addChangeListener(::javax::swing::event::ChangeListener *);
  virtual void removeChangeListener(::javax::swing::event::ChangeListener *);
public: // actually protected
  virtual void fireStateChanged();
public:
  virtual JArray< ::javax::swing::event::ChangeListener * > * getChangeListeners();
  virtual ::javax::swing::SingleSelectionModel * getModel();
  virtual void setModel(::javax::swing::SingleSelectionModel *);
  virtual jint getTabPlacement();
  virtual void setTabPlacement(jint);
  virtual jint getTabLayoutPolicy();
  virtual void setTabLayoutPolicy(jint);
  virtual jint getSelectedIndex();
private:
  void checkIndex(jint, jint, jint);
public:
  virtual void setSelectedIndex(jint);
  virtual ::java::awt::Component * getSelectedComponent();
  virtual void setSelectedComponent(::java::awt::Component *);
  virtual void insertTab(::java::lang::String *, ::javax::swing::Icon *, ::java::awt::Component *, ::java::lang::String *, jint);
  virtual void addTab(::java::lang::String *, ::javax::swing::Icon *, ::java::awt::Component *, ::java::lang::String *);
  virtual void addTab(::java::lang::String *, ::javax::swing::Icon *, ::java::awt::Component *);
  virtual void addTab(::java::lang::String *, ::java::awt::Component *);
  virtual ::java::awt::Component * add(::java::awt::Component *);
  virtual ::java::awt::Component * add(::java::lang::String *, ::java::awt::Component *);
  virtual ::java::awt::Component * add(::java::awt::Component *, jint);
  virtual void add(::java::awt::Component *, ::java::lang::Object *);
  virtual void add(::java::awt::Component *, ::java::lang::Object *, jint);
  virtual void removeTabAt(jint);
  virtual void remove(::java::awt::Component *);
  virtual void remove(jint);
  virtual void removeAll();
  virtual jint getTabCount();
  virtual jint getTabRunCount();
  virtual ::java::lang::String * getTitleAt(jint);
  virtual ::javax::swing::Icon * getIconAt(jint);
  virtual ::javax::swing::Icon * getDisabledIconAt(jint);
  virtual ::java::lang::String * getToolTipTextAt(jint);
  virtual ::java::awt::Color * getForegroundAt(jint);
  virtual ::java::awt::Color * getBackgroundAt(jint);
  virtual ::java::awt::Component * getComponentAt(jint);
  virtual jboolean isEnabledAt(jint);
  virtual jint getMnemonicAt(jint);
  virtual jint getDisplayedMnemonicIndexAt(jint);
  virtual ::java::awt::Rectangle * getBoundsAt(jint);
  virtual void setTitleAt(jint, ::java::lang::String *);
  virtual void setIconAt(jint, ::javax::swing::Icon *);
  virtual void setDisabledIconAt(jint, ::javax::swing::Icon *);
  virtual void setToolTipTextAt(jint, ::java::lang::String *);
  virtual void setBackgroundAt(jint, ::java::awt::Color *);
  virtual void setForegroundAt(jint, ::java::awt::Color *);
  virtual void setEnabledAt(jint, jboolean);
  virtual void setComponentAt(jint, ::java::awt::Component *);
  virtual void setDisplayedMnemonicIndexAt(jint, jint);
  virtual void setMnemonicAt(jint, jint);
  virtual jint indexOfTab(::java::lang::String *);
  virtual jint indexOfTab(::javax::swing::Icon *);
  virtual jint indexOfComponent(::java::awt::Component *);
  virtual jint indexAtLocation(jint, jint);
  virtual ::java::lang::String * getToolTipText(::java::awt::event::MouseEvent *);
public: // actually protected
  virtual ::java::lang::String * paramString();
public:
  virtual ::javax::accessibility::AccessibleContext * getAccessibleContext();
private:
  static const jlong serialVersionUID = 1614381073220130939LL;
public: // actually protected
  ::javax::swing::event::ChangeEvent * __attribute__((aligned(__alignof__( ::javax::swing::JComponent)))) changeEvent;
  ::javax::swing::event::ChangeListener * changeListener;
  ::javax::swing::SingleSelectionModel * model;
public:
  static const jint SCROLL_TAB_LAYOUT = 1;
  static const jint WRAP_TAB_LAYOUT = 0;
public: // actually protected
  jint tabPlacement;
private:
  jint layoutPolicy;
public: // actually package-private
  ::java::util::Vector * tabs;
public:
  static ::java::lang::Class class$;
};

#endif // __javax_swing_JTabbedPane__
