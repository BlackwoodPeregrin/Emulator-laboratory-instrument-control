TASK=test_task

task : sources/main.cpp sources/emulator.cpp sources/laboratory_instrument.cpp sources/interface.cpp
	g++ sources/main.cpp sources/emulator.cpp sources/laboratory_instrument.cpp sources/interface.cpp -o task

clean:
	-rm task

dist : clean
	rm -rf $(TASK)
	-mkdir $(TASK)
	cp -r ./headers $(TASK)/
	cp -r ./sources $(TASK)/
	cp makefile $(TASK)/
	tar -cvzf ./$(TASK).tgz $(TASK)/
	rm -rf $(TASK)/
