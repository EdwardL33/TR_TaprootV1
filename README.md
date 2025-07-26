## Follow RHIT setup to get taproot ##
link: https://agmui.github.io/notion2hugo_test/docs/guides/taproot-basics/setting-up-taproot/  <br>
I recommend the google slides: https://docs.google.com/presentation/d/1WCKfnT1pG3GdZT9Rh7dKZLlVS0-GOQzeXyLNWM2VdPk/edit?usp=sharing 

## CURRENT WAY TO FLASH ##

### INITAL SETUP ###
- go into main folder (Taproot_Proposal)
- ```cd template-project```
- ```pipenv install --python="3.9"``` (pipenv --rm (if you mess up))
- ```pipenv shell (type exit to leave pipenv)```

### REGENERATE TAPROOT TO ADD MODULES ###
(if you're in \template-project\ directory)
```
cd ..;                                        
rm -r template-project\taproot; 
cd .\template-project\;
lbuild build; 
scons build
```

### BUILDING AND FLASHING ###
- ```pipenv shell```
- ```scons build```
- ```openocd -f interface/stlink.cfg -f target/stm32f4x.cfg  -c "program ./build/hardware/scons-release/template-project.elf verify reset exit"```

## ADDING NEW BOARD ##
TODO

## FILES MODIFIED OR ADDED ##

```
template-project/
├── project.xml                # edited
└── src/
    └── main.cpp              # main file!!!

taproot/
├── modm-project-files/
│   ├── module.lb             # edited, added board to MCU_VARIANTS_BY_BOARD and DEFAULT_MODM_OPTIONS_BY_BOARD
│   └── project.xml.in        # edited, added board elif
│
├── src/
│   └── tap/
│       ├── board/
│       │   └── stm32-f446re/             # new folder
│       │       └── board.hpp.in          # new file, grabbed from modm
│       │
│       ├── communication/
│       │   └── gpio/
│       │       ├── leds.cpp.in           # edited
│       │       └── leds.hpp.in           # edited
│       │
│       ├── sensors/
│       │   └── buzzer/
│       │       └── module.lb             # ?????????
│       │
│       └── serial/
│           └── module.lb                 # edited, added board remote uart
│
├── supported-devices/
│   └── stm32-f446re.xml      # new file
│
└── repo.lb                   # edited, added board to enumeration
```
