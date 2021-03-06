﻿/***********************************************************************************
**
** GUICheckbox.cpp
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#include "GUICheckbox.h"
#include "../OrionUO.h"
#include "../SelectedObject.h"
#include "../Managers/MouseManager.h"
//----------------------------------------------------------------------------------
CGUICheckbox::CGUICheckbox(const uint &serial, const ushort &graphic, const ushort &graphicChecked, const ushort &graphicDisabled, const int &x, const int &y)
: CGUIDrawObject(GOT_CHECKBOX, serial, graphic, 0, x, y), m_GraphicChecked(graphicChecked),
m_GraphicSelected(graphic), m_GraphicDisabled(graphicDisabled), m_Checked(false),
m_TextPosition(STP_RIGHT), m_TextX(0), m_TextY(0), m_DefaultTextOffset(2)
{
}
//----------------------------------------------------------------------------------
CGUICheckbox::~CGUICheckbox()
{
	m_Text.Clear();
}
//----------------------------------------------------------------------------------
void CGUICheckbox::SetTextParameters(const uchar &font, const wstring &text, const ushort &color, const SLIDER_TEXT_POSITION &textPosition, const int &textWidth, const TEXT_ALIGN_TYPE &align, const ushort &textFlags)
{
	m_TextPosition = textPosition;
	g_FontManager.GenerateW(font, m_Text, text.c_str(), color, 30, textWidth, align, textFlags);
	UpdateTextPosition();
}
//----------------------------------------------------------------------------------
void CGUICheckbox::SetTextParameters(const uchar &font, const string &text, const ushort &color, const SLIDER_TEXT_POSITION &textPosition, const int &textWidth, const TEXT_ALIGN_TYPE &align, const ushort &textFlags)
{
	m_TextPosition = textPosition;
	g_FontManager.GenerateA(font, m_Text, text.c_str(), color, textWidth, align, textFlags);
	UpdateTextPosition();
}
//----------------------------------------------------------------------------------
void CGUICheckbox::UpdateTextPosition()
{
	int textX = m_X;
	int textY = m_Y;

	CGLTexture *th = g_Orion.ExecuteGump(m_Graphic);

	if (th != NULL)
	{
		switch (m_TextPosition)
		{
			case STP_TOP:
			case STP_TOP_CENTER:
			{
				textY -= m_Text.Height - m_DefaultTextOffset;

				break;
			}
			case STP_BOTTOM:
			case STP_BOTTOM_CENTER:
			{
				textY += th->Height + m_DefaultTextOffset;

				break;
			}
			case STP_LEFT:
				//textY -= 4;
			case STP_LEFT_CENTER:
			{
				textX -= m_Text.Width - m_DefaultTextOffset;

				break;
			}
			case STP_RIGHT:
				//textY -= 4;
			case STP_RIGHT_CENTER:
			{
				textX += th->Width + m_DefaultTextOffset;

				break;
			}
			default:
				break;
		}

		switch (m_TextPosition)
		{
			case STP_TOP_CENTER:
			case STP_BOTTOM_CENTER:
			{
				int textWidth = m_Text.Width;
				int sliderWidth = th->Width;

				int deltaX = abs(sliderWidth - textWidth) / 2;

				if (sliderWidth > textWidth)
					textX += deltaX;
				else
					textX -= deltaX;

				break;
			}
			case STP_LEFT_CENTER:
			case STP_RIGHT_CENTER:
			{
				int textHeight = m_Text.Height;
				int sliderHeight = th->Height;

				int deltaY = abs(sliderHeight - textHeight) / 2;

				if (sliderHeight > textHeight)
					textY += deltaY;
				else
					textY -= deltaY;

				break;
			}
			default:
				break;
		}
	}

	m_TextX = textX;
	m_TextY = textY;
}
//----------------------------------------------------------------------------------
void CGUICheckbox::PrepareTextures()
{
	g_Orion.ExecuteGump(m_Graphic);
	g_Orion.ExecuteGump(m_GraphicChecked);
	g_Orion.ExecuteGump(m_GraphicDisabled);
}
//----------------------------------------------------------------------------------
ushort CGUICheckbox::GetDrawGraphic()
{
	ushort graphic = m_Graphic;

	if (!m_Enabled)
		graphic = m_GraphicDisabled;
	else if (m_Checked)
		graphic = m_GraphicChecked;
	else if (g_SelectedObject.Object() == this)
		graphic = m_GraphicSelected;

	return graphic;
}
//----------------------------------------------------------------------------------
void CGUICheckbox::Draw(const bool &checktrans)
{
	CGUIDrawObject::Draw(checktrans);

	m_Text.Draw(m_TextX, m_TextY, checktrans);
}
//----------------------------------------------------------------------------------
bool CGUICheckbox::Select()
{
	bool result = CGUIDrawObject::Select();

	if (!result && !m_Text.Empty())
	{
		int x = g_MouseManager.Position.X - m_TextX;
		int y = g_MouseManager.Position.Y - m_TextY;

		result = (x >= 0 && y >= 0 && x < m_Text.Width && y < m_Text.Height);
	}

	return result;
}
//----------------------------------------------------------------------------------
void CGUICheckbox::OnMouseEnter()
{
	if (m_Graphic != m_GraphicSelected && g_SelectedObject.Gump() != NULL)
		g_SelectedObject.Gump()->WantRedraw = true;
}
//----------------------------------------------------------------------------------
void CGUICheckbox::OnMouseExit()
{
	if (m_Graphic != m_GraphicSelected && g_LastSelectedObject.Gump() != NULL)
		g_LastSelectedObject.Gump()->WantRedraw = true;
}
//----------------------------------------------------------------------------------
