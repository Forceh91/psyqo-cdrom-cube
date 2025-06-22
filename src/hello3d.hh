#ifndef _HELLO3D_H_
#define _HELLO3D_H_

#include "psyqo/application.hh"
#include "psyqo/trigonometry.hh"
#include "psyqo/advancedpad.hh"
#include "psyqo/coroutine.hh"

class MadnightEngine final : public psyqo::Application
{
    void prepare() override;
    void createScene() override;
    psyqo::Coroutine<> SubCreateScene();

public:
    psyqo::Trig<> m_trig;
    psyqo::AdvancedPad m_input;
};

extern MadnightEngine g_madnightEngine;

#endif
