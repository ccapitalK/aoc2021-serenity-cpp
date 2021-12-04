TODO:
    [ ] Render hard tabs in HS
    [ ] [Feature] Ctrl+Tab shift through recent files in HS
    [ ] `for (auto line: file->lines())`
    [ ] Queue commands in HS (Ctrl+B -> Ctrl+R)
    [ ] Spice agent doesn't work
    [ ] Fix weird error messages for ssh (Invalid line seperator or something)
    [ ] Icon for Makefiles
    [ ] [No Repro] Fatal Error: The input '/tmp/SOMETHING.s' and output 'main.o' files are the same
    [x] Weird tab inputs into HS (might be from Alt+Tab into QEMU)
    [ ] [Difficult Repro] HS crashed when debugging crash
    [ ] HackStudio doesn't enable all the cool header shit because that's done through Serenity's CMake config
        [ ] E.G. outln() compile time format check doesn't work
    [ ] [Feature] Add clang-format on save if available
    [ ] Hack Studio should remember where the last project was created if it hasn't been closed since then (during the new project wizard)
    [ ] [Feature] Make configuration option for number of lines of overscroll to bring into view when writing with cursor off screen
    [ ] Crash in HS:
		7634.597 HackStudio(53:53): ASSERTION FAILED: m_history_start == 0                                                                                                         
		./Userland/Libraries/LibVT/Terminal.h:392                                                                                                                                  
		7634.597 [#0 HackStudio(53:53)]: Terminating HackStudio(53) due to signal 6                                                                                                
		7634.597 [#0 FinalizerTask(4:4)]: 0xdeadc0de  Kernel::Processor::switch_context(Kernel::Thread*&, Kernel::Thread*&) + 0x572                                                                                            
		0xdeadc0de  Kernel::Scheduler::context_switch(Kernel::Thread*) [clone .localalias] + 0x40e                                                                                 
		0xdeadc0de  Kernel::Scheduler::pick_next() [clone .localalias] + 0x12f                                                                                                     
		0xdeadc0de  Kernel::Processor::check_invoke_scheduler() [clone .localalias] + 0x214                                                                                        
		0xdeadc0de  Kernel::Thread::die_if_needed() [clone .localalias] + 0x1bb                                                                                                    
		0xdeadc0de  syscall_handler + 0x2370                                                                                                                                       
		0xdeadc0de  syscall_asm_entry + 0x31                                                                                                                                       
		0x4d7d53e5  libc.so: .text + 0x163e5                                                                                                                                       
		0x4d7c098a  libc.so: .text + 0x198a                                                                                                                                        
		0x4d7c141d  libc.so: .text + 0x241d                                                                                                                                        
		0x94c07ebe  libvt.so.serenity: .text + 0x7ebe                                                                                                                              
		0x94c08521  libvt.so.serenity: .text + 0x8521                                                                                                                              
		0x94c08619  libvt.so.serenity: .text + 0x8619                                                                                                                              
		0x94c19fe0  libvt.so.serenity: .text + 0x19fe0                                                                                                                             
		0x94c0b8ea  libvt.so.serenity: .text + 0xb8ea                                                                                                                              
		0x94c07464  libvt.so.serenity: .text + 0x7464                                                                                                                              
		0x94c1023f  libvt.so.serenity: .text + 0x1023f                                                                                                                             
		0x1da7548a  libcore.so.serenity: .text + 0x2b48a                                                                                                                           
		0x1da76781  libcore.so.serenity: .text + 0x2c781                                                                                                                           
		0x1da617f1  libcore.so.serenity: .text + 0x177f1                                                                                                                           
		0x1da6233b  libcore.so.serenity: .text + 0x1833b                                                                                                                           
		0x3bdb4788  libgui.so.serenity: .text + 0x20788                                                                                                                            
		0x5f0a22bd  /bin/HackStudio: .text + 0x682bd                                                                                                                               
		0x404eb1c2  libmain.so.serenity: .text + 0x1c2                                       
		0x5f03c1fd  /bin/HackStudio: .text + 0x21fd                                                                                                                                
		                                                                                                                                                                           
		7634.606 [#0 FinalizerTask(4:4)]: Generating coredump for pid: 53                                                                                                          
		7634.892 CrashDaemon(16:16): New coredump file: /tmp/coredump/HackStudio_53_1638617948                                                                                     
		7634.912 [#0 g++(711:711)]: Terminating g++(711) due to signal 1                                                                                                           
		7636.512 CrashReporter(712:712): Generating backtrace took 1507 ms                                                                                                         
		7636.512 CrashReporter(712:712): --- Backtrace for thread #0 (TID 53) ---                                                                                                  
		7636.512 CrashReporter(712:712): 0x6258902e: [libsystem.so] syscall2 +0xe (syscall.cpp:25 => syscall.cpp:24)                                                               
		7636.512 CrashReporter(712:712): 0x4d7d53e4: [libc.so] raise +0x24 (syscall.h:35 => signal.cpp:21 => signal.cpp:34)                                                        
		7636.512 CrashReporter(712:712): 0x4d7c0989: [libc.so] abort +0x29 (stdlib.cpp:215)                                                                                        
		7636.516 CrashReporter(712:712): 0x4d7c141c: [libc.so] __assertion_failed +0x6c (assert.cpp:33)                                                                            
		7636.516 CrashReporter(712:712): 0x94c07ebd: [libvt.so.serenity] VT::Terminal::scroll_up(unsigned short, unsigned short, unsigned long) [clone .localalias] +0x5ed (Terminal.h:392 => Terminal.cpp:783)
		7636.516 CrashReporter(712:712): 0x94c08520: [libvt.so.serenity] VT::Terminal::linefeed() [clone .localalias] +0xe0 (Terminal.cpp:756 => Terminal.cpp:738)                                                             
		7636.516 CrashReporter(712:712): 0x94c08618: [libvt.so.serenity] .L1818 +0x48 (Terminal.cpp:1055)                                                                                             
		7636.516 CrashReporter(712:712): 0x94c19fdf: [libvt.so.serenity] .L191 +0xf (EscapeSequenceParser.cpp:58)                                                                                     
		7636.516 CrashReporter(712:712): 0x94c0b8e9: [libvt.so.serenity] AK::Function<void (VT::EscapeSequenceStateMachine::Action, unsigned char)>::operator()(VT::EscapeSequenceStateMachine::Action, unsigned char) const +0x69 (Function.h:91)
		7636.516 CrashReporter(712:712): 0x94c07463: [libvt.so.serenity] .L1339 +0x33 (EscapeSequenceStateMachine.h:81 => EscapeSequenceParser.h:45 => Terminal.cpp:996)
		7636.516 CrashReporter(712:712): 0x94c1023e: [libvt.so.serenity] VT::TerminalWidget::set_pty_master_fd(int)::{lambda()#1}::operator()() const +0x8e (TerminalWidget.cpp:72)                                            
		7636.521 CrashReporter(712:712): 0x1da75489: [libcore.so.serenity] Core::Notifier::event(Core::Event&) +0x99 (Function.h:91)
		7636.521 CrashReporter(712:712): 0x1da76780: [libcore.so.serenity] Core::Object::dispatch_event(Core::Event&, Core::Object*) +0xb0 (Object.cpp:219)
		7636.521 CrashReporter(712:712): 0x1da617f0: [libcore.so.serenity] Core::EventLoop::pump(Core::EventLoop::WaitMode) +0x180 (EventLoop.cpp:413)
		7636.521 CrashReporter(712:712): 0x1da6233a: [libcore.so.serenity] Core::EventLoop::exec() +0x6a (EventLoop.cpp:370)
		7636.521 CrashReporter(712:712): 0x3bdb4787: [libgui.so.serenity] GUI::Application::exec() +0x27 (Application.cpp:119)
		7636.521 CrashReporter(712:712): 0x5f0a22bc: [/bin/HackStudio] serenity_main(Main::Arguments) +0x96c (main.cpp:85)
		7636.521 CrashReporter(712:712): 0x404eb1c1: [libmain.so.serenity] main +0x81 (Main.cpp:24)
		7636.521 CrashReporter(712:712): 0x5f03c1fc: [/bin/HackStudio] _entry +0x5c (crt0.cpp:46)
		7636.598 CrashReporter(712:712): perror(): unveil: Operation not permitted
		7636.600 [#0 FinalizerTask(4:4)]: Process 'CrashReporter' exited with the veil left open
    [ ] [Feature] Recent projects menu in Hack Studio
