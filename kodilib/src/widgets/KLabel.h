/*
 *  KLabel.h
 *  kodisein
 */

#ifndef __KLabel
#define __KLabel

#include "KWidget.h"
#include <stdarg.h>

enum {	KDL_LABEL_FLAG_LARGE_FONT = KDL_WIDGET_FLAG_END,
        KDL_LABEL_FLAG_END };
        
class KLabel : public KWidget
{
    INTROSPECTION
    
    protected:
    
    std::string              text;
    virtual void	updateTextSize	 	();
    
    public:
                        KLabel                  ( const std::string & = "" );
                                
    virtual void	render                  ();
    virtual void	update                  ();
    virtual void	clear			() { setText(""); }
    virtual void        setText                 ( const std::string & n );
    virtual void	setSize			( KSize );
    virtual void	setTextCols		( int c ) { setTextSize(KSize(c, getTextRows())); }
    virtual void	setTextSize		( KSize );
    virtual void	setLargeFont		( bool = true );
    bool		isLargeFont		() const { return flags[KDL_LABEL_FLAG_LARGE_FONT]; }
    
    virtual std::string      getText                 () const { return text; }
    
    int			getTextRows		() const { return ((size.h - 5) / getRowHeight()); }
    int			getTextCols		() const { return ((size.w - 10) / getColumnWidth()); }
    KSize		getTextSize		() const { return KSize(getTextCols(), getTextRows()); }
    int			getColumnWidth		() const { return (flags[KDL_LABEL_FLAG_LARGE_FONT] ? 9 : 8); }
    int			getRowHeight		() const { return (flags[KDL_LABEL_FLAG_LARGE_FONT] ? 15 : 13); }
};

#endif

