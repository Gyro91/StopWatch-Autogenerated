function WI(block)
% Level-2 M file S-Function for interface demo.
%   Copyright 1990-2004 The MathWorks, Inc.
%   $Revision: 1.1.6.1 $ 

  setup(block);
  
%endfunction

function setup(block)
  global timebutton
  global timesetbutton
  global alarmbutton
  global plusbutton
  global minusbutton
  global swatchbutton
  global startbutton
  global stopbutton

  %% Register dialog parameters: No parameters for this block 
  block.NumDialogPrms = 0;
  %% Register number of input and output ports
  block.NumInputPorts  = 6;

  %% Setup functional port properties to dynamically
  %% inherited.
  block.SetPreCompInpPortInfoToDynamic;                    % port inherits sample rates

  %% Input 1 is for hours
  block.InputPort(1).Complexity   = 'Real'; 
  block.InputPort(1).DataTypeId   = 3;                     % 8 for boolean, 0 for double, 3 for uint8 4 for int8
  block.InputPort(1).SamplingMode = 'Sample';
  block.InputPort(1).Dimensions   = 1;
  block.InputPort(1).DirectFeedthrough   = 0;

  %% Input 2 is for minutes
  block.InputPort(2).Complexity   = 'Real'; 
  block.InputPort(2).DataTypeId   = 3;                     % 8 for boolean, 0 for double, 3 for uint8 4 for int8
  block.InputPort(2).SamplingMode = 'Sample';
  block.InputPort(2).Dimensions   = 1;
  block.InputPort(2).DirectFeedthrough   = 0;

  %% Input 3 is for seconds
  block.InputPort(3).Complexity   = 'Real'; 
  block.InputPort(3).DataTypeId   = 3;                     % 8 for boolean, 0 for double, 3 for uint8 4 for int8
  block.InputPort(3).SamplingMode = 'Sample';
  block.InputPort(3).Dimensions   = 1;
  block.InputPort(3).DirectFeedthrough   = 0;

  %% Input 4 is for tenths
  block.InputPort(4).Complexity   = 'Real'; 
  block.InputPort(4).DataTypeId   = 3;                     % 8 for boolean, 0 for double, 3 for uint8 4 for int8
  block.InputPort(4).SamplingMode = 'Sample';
  block.InputPort(4).Dimensions   = 1;
  block.InputPort(4).DirectFeedthrough   = 0;

  %% Input 5 is for mode
  block.InputPort(5).Complexity   = 'Real'; 
  block.InputPort(5).DataTypeId   = 3;                     % 8 for boolean, 0 for double, 3 for uint8 4 for int8
  block.InputPort(5).SamplingMode = 'Sample';
  block.InputPort(5).Dimensions   = 1;
  block.InputPort(5).DirectFeedthrough   = 0;
 
  %% Input 6 is for it's time for the alarm
  block.InputPort(6).Complexity   = 'Real'; 
  block.InputPort(6).DataTypeId   = 3;                     % 8 for boolean, 0 for double, 3 for uint8 4 for int8
  block.InputPort(6).SamplingMode = 'Sample';
  block.InputPort(6).Dimensions   = 1;
  block.InputPort(6).DirectFeedthrough   = 0;
  
  block.NumOutputPorts = 8;

  %% Setup functional port properties to dynamically
  %% inherited.
  block.SetPreCompOutPortInfoToDynamic;

  block.OutputPort(1).Complexity   = 'Real'; 
  block.OutputPort(1).DataTypeId   = 8;                     % 8 for boolean, 0 for double, 3 for uint8 4 for int8
  block.OutputPort(1).SamplingMode = 'Sample';
  block.OutputPort(1).Dimensions   = 1;

  block.OutputPort(2).Complexity   = 'Real'; 
  block.OutputPort(2).DataTypeId   = 8;                     % 8 for boolean, 0 for double, 3 for uint8 4 for int8
  block.OutputPort(2).SamplingMode = 'Sample';
  block.OutputPort(2).Dimensions   = 1;

  block.OutputPort(3).Complexity   = 'Real'; 
  block.OutputPort(3).DataTypeId   = 8;                     % 8 for boolean, 0 for double, 3 for uint8 4 for int8
  block.OutputPort(3).SamplingMode = 'Sample';
  block.OutputPort(3).Dimensions   = 1;

  block.OutputPort(4).Complexity   = 'Real'; 
  block.OutputPort(4).DataTypeId   = 8;                     % 8 for boolean, 0 for double, 3 for uint8 4 for int8
  block.OutputPort(4).SamplingMode = 'Sample';
  block.OutputPort(4).Dimensions   = 1;

  block.OutputPort(5).Complexity   = 'Real'; 
  block.OutputPort(5).DataTypeId   = 8;                     % 8 for boolean, 0 for double, 3 for uint8 4 for int8
  block.OutputPort(5).SamplingMode = 'Sample';
  block.OutputPort(5).Dimensions   = 1;

  block.OutputPort(6).Complexity   = 'Real'; 
  block.OutputPort(6).DataTypeId   = 8;                     % 8 for boolean, 0 for double, 3 for uint8 4 for int8
  block.OutputPort(6).SamplingMode = 'Sample';
  block.OutputPort(6).Dimensions   = 1;

  
  block.OutputPort(7).Complexity   = 'Real'; 
  block.OutputPort(7).DataTypeId   = 8;                     % 8 for boolean, 0 for double, 3 for uint8 4 for int8
  block.OutputPort(7).SamplingMode = 'Sample';
  block.OutputPort(7).Dimensions   = 1;
  
  block.OutputPort(8).Complexity   = 'Real'; 
  block.OutputPort(8).DataTypeId   = 8;                     % 8 for boolean, 0 for double, 3 for uint8 4 for int8
  block.OutputPort(8).SamplingMode = 'Sample';
  block.OutputPort(8).Dimensions   = 1;


  %% Register methods
  block.RegBlockMethod('SetInputPortSamplingMode',@SetInputPortSamplingMode);
  block.RegBlockMethod('Start',                   @Start);  
  %   block.RegBlockMethod('WriteRTW',                @WriteRTW);
  block.RegBlockMethod('Outputs',                 @Outputs);

  timebutton = 0;
  timesetbutton = 0;
  alarmbutton = 0;
  plusbutton = 0;
  minusbutton = 0;
  swatchbutton = 0;
  startbutton = 0;
  stopbutton = 0;
  
  %endfunction

 function SetInputPortSamplingMode(block, idx, fd)
   block.InputPort(idx).SamplingMode = fd;

function ButtonDown(hObj,evnt)
   global timebutton
   global timesetbutton
   global alarmbutton
   global plusbutton
   global minusbutton
   global swatchbutton
   global startbutton
   global stopbutton

  pos = get(hObj,'CurrentPoint');

 if ((pos(2) > (240 - 45)) && (pos(2) < 240) && (pos(1) > 0) && (pos(1) < 80))
            timebutton=1;
  end;
  if ((pos(2) > (240 - 45)) && (pos(2) < 240) && (pos(1) > 80) && (pos(1) < 160))
            timesetbutton=1;
  end;
  if ((pos(2) > (240 - 45)) && (pos(2) < 240) && (pos(1) > 160) && (pos(1) < 240))
            alarmbutton=1;
  end;
  if ((pos(2) < 240-63) && (pos(2) > 240-96) && (pos(1) > 270) && (pos(1) <(305)))
            plusbutton=1;
  end;
  if ((pos(2) < 240-121) && (pos(2) > 240-153) && (pos(1) > 270) && (pos(1) <(305)))
            minusbutton=1;
  end;
  if ((pos(2) > (240-45)) && (pos(2) < 240) && (pos(1) > 240) && (pos(1) < 320))
            swatchbutton=1;
  end;
  if ((pos(2) > (40)) && (pos(2) < 70) && (pos(1) > 50) && (pos(1) < 130))
            startbutton=1;
  end;
  
   if ((pos(2) > (40)) && (pos(2) < 70) && (pos(1) > 150) && (pos(1) < 230))
            stopbutton=1;
  end;

function ButtonUp(hObj,evnt)
   global timebutton
   global timesetbutton
   global alarmbutton
   global plusbutton
   global minusbutton
   global swatchbutton
   global startbutton
   global stopbutton
   
  pos = get(hObj,'CurrentPoint');

  if ((pos(2) > (240 - 45)) && (pos(2) < 240) && (pos(1) > 0) && (pos(1) < 80))
            timebutton=0;
  end;
  if ((pos(2) > (240 - 45)) && (pos(2) < 240) && (pos(1) > 80) && (pos(1) < 160))
            timesetbutton=0;
  end;
  if ((pos(2) > (240 - 45)) && (pos(2) < 240) && (pos(1) > 160) && (pos(1) < 240))
            alarmbutton=0;
  end;
  if ((pos(2) < 240-63) && (pos(2) > 240-96) && (pos(1) > 270) && (pos(1) <(305)))
            plusbutton=0;
  end;
   if ((pos(2) < 240-121) && (pos(2) > 240-153) && (pos(1) > 270) && (pos(1) <(305)))
            minusbutton=0;
  end;
  if ((pos(2) > (240-45)) && (pos(2) < 240) && (pos(1) > 240) && (pos(1) < 360))
            swatchbutton=0;
  end;
  if ((pos(2) > (40)) && (pos(2) < 70) && (pos(1) > 50) && (pos(1) < 130))
            startbutton=0;
  end;
  if ((pos(2) > (40)) && (pos(2) < 70) && (pos(1) > 150) && (pos(1) < 230))
            stopbutton=0;
  end;


function Start(block) 

  global IM
  global FH
  global timemode_hnd;
  global timesetmode_hnd;
  global alarmsetmode_hnd;
  global swatchmode_hnd;
  global start_hnd;
  global stop_hnd;
  global alarm_hnd;
  
  global hrs_digits;
  global min_digits;
  global sec_digits;
  global ten_digits;
 
  global timemode;
  global timesetmode;
  global alarmsetmode;
  global swatchmode;
  global start;
  global stop;
  global alarm;
  
  global sep2;
  global sep3;

  IM = imread('images/background.png');
  timemode = imread('images/watchhover.png');
  timesetmode = imread('images/timerhover.png');
  alarmsetmode = imread('images/alarmhover.png');
  swatchmode = imread('images/swatchhover.png');
  start = imread('images/start.png');
  stop = imread('images/stop.png');
  alarm = imread('images/wakesup.png');
  
  bhD = @ButtonDown;
  bhU = @ButtonUp;

% background image 

  FH = figure('Toolbar', 'none', 'Menubar', 'none', 'Name', 'Figname', 'WindowButtonDownFcn', bhD, 'WindowButtonUpFcn', bhU, 'Resize', 'off');
  scrsz = get(0,'ScreenSize');
  set(FH, 'Units','pixels');
  set(FH, 'Position',[1 scrsz(4)-500 320 240]);
  hax = axes('Units', 'pixels', 'Position', [1, 1, 320, 240], 'Visible', 'off');
  image(IM)
  axis off

% text output 

% skipping Arial
  hrs_digits = text(33+14, 240 - 85,'', 'Units', 'pixels', 'FontUnits', 'points', 'FontSize', 32);
  set(hrs_digits, 'Color',[1 1 1]);
  set(hrs_digits, 'VerticalAlignment','top');
  set(hrs_digits, 'FontName', 'Arial');

  sep1 = text(81+14, 240 - 85,'', 'Units', 'pixels', 'FontUnits', 'points', 'FontSize', 32);
  set(sep1, 'Color',[1 1 1]);
  set(sep1, 'VerticalAlignment','top');
  set(sep1, 'FontName', 'Arial');
  set(sep1, 'string', ':');

  min_digits = text(89 + 14, 240 - 85,'', 'Units', 'pixels', 'FontUnits', 'points', 'FontSize', 32);
  set(min_digits, 'Color',[1 1 1]);
  set(min_digits, 'VerticalAlignment','top');
  set(min_digits, 'FontName', 'Arial');

  sep2 = text(134 + 14, 240 - 85,'', 'Units', 'pixels', 'FontUnits', 'points', 'FontSize', 32);
  set(sep2, 'Color',[1 1 1]);
  set(sep2, 'VerticalAlignment','top');
  set(sep2, 'FontName', 'Arial');
  set(sep2, 'string', ':');

  sec_digits = text(145+14, 240 - 85,'', 'Units', 'pixels', 'FontUnits', 'points', 'FontSize', 32);
  set(sec_digits, 'Color',[1 1 1]);
  set(sec_digits, 'VerticalAlignment','top');
  set(sec_digits, 'FontName', 'Arial');

  sep3 = text(188+14, 240 - 85,'', 'Units', 'pixels', 'FontUnits', 'points', 'FontSize', 32);
  set(sep3, 'Color',[1 1 1]);
  set(sep3, 'VerticalAlignment','top');
  set(sep3, 'FontName', 'Arial');
  set(sep3, 'string', '.');

  ten_digits = text(199+14, 240 - 85,'', 'Units', 'pixels', 'FontUnits', 'points', 'FontSize', 32);
  set(ten_digits, 'Color',[1 1 1]);
  set(ten_digits, 'VerticalAlignment','top');
  set(ten_digits, 'FontName', 'Arial');

  hax = axes('Units', 'pixels', 'Position', [0, 240-45, 80, 45], 'Visible', 'off');
  timemode_hnd = image(timemode, 'Visible', 'off');
  axis off;
  hax = axes('Units', 'pixels', 'Position', [80, 240-45, 80, 45], 'Visible', 'off');
  timesetmode_hnd = image(timesetmode, 'Visible', 'off');
  axis off;
  hax = axes('Units', 'pixels', 'Position', [160, 240-45, 80, 45], 'Visible', 'off');
  alarmsetmode_hnd = image(alarmsetmode, 'Visible', 'off');
  axis off;
  hax = axes('Units', 'pixels', 'Position', [240, 240-45, 80, 45], 'Visible', 'off');
  swatchmode_hnd = image(swatchmode, 'Visible', 'off');
  axis off;
  hax = axes('Units', 'pixels', 'Position', [50, 40, 80, 30], 'Visible', 'off');
  start_hnd = image(start, 'Visible', 'on');
  axis off;
  hax = axes('Units', 'pixels', 'Position', [150, 40, 80, 30], 'Visible', 'off');
  stop_hnd = image(stop, 'Visible', 'on');
  axis off;
  hax = axes('Units', 'pixels', 'Position', [250, 20, 50, 50], 'Visible', 'off');
  alarm_hnd = image(alarm, 'Visible', 'off');
  axis off;

%endfunction

function con_str = convertDto2S(dig)
  shw_val = mod(dig, 100);
  con_str = int2str(shw_val);
  if shw_val < 10 
      con_str = strcat('0',con_str);
  end
%endfunction

function con_str = convertDto1S(dig)
  shw_val = mod(dig, 10);
  con_str = int2str(shw_val);
%endfunction

    function Outputs(block)
  
   global timebutton
   global timesetbutton
   global alarmbutton
   global plusbutton
   global minusbutton
   global swatchbutton
   global startbutton
   global stopbutton
   
 
   global timemode_hnd;
   global timesetmode_hnd;
   global alarmsetmode_hnd;
   global swatchmode_hnd;
   global alarm_hnd;
   
   global hrs_digits;
   global min_digits;
   global sec_digits;
   global ten_digits;
 
   global sep2;
   global sep3;

%Update graphics based on input ports

%% Need to transform block.InputPort(1).Data value into string of 2 chars
  set(hrs_digits, 'string',  convertDto2S(block.InputPort(1).Data))
%% Need to transform block.InputPort(2).Data value into string of 2 chars
  set(min_digits, 'string', convertDto2S(block.InputPort(2).Data))
%% Need to transform block.InputPort(3).Data value into string of 2 chars
%% Attention!! display is on only if mode is time or stopwatch
  if (block.InputPort(5).Data == 3) || (block.InputPort(5).Data == 0) || (block.InputPort(5).Data == 1) 
    set(sec_digits, 'Visible', 'on')
    set(sec_digits, 'string', convertDto2S(block.InputPort(3).Data))
    set(sep2, 'Visible', 'on')
  else
    set(sec_digits, 'Visible', 'off')
    set(sep2, 'Visible', 'off')
  end;
%% Need to transform block.InputPort(4).Data value into string of 1 char
%% Attention!! display is on only if mode is stopwatch
  if block.InputPort(5).Data == 3  
    set(ten_digits, 'Visible', 'on')
    set(ten_digits, 'string', convertDto1S(block.InputPort(4).Data))
    set(sep3, 'Visible', 'on')
  else
    set(ten_digits, 'Visible', 'off')
    set(sep3, 'Visible', 'off')
  end;
  
  if block.InputPort(5).Data == 0 
      set(timemode_hnd, 'Visible', 'on')
  else
      set(timemode_hnd, 'Visible', 'off')
  end;

  if block.InputPort(5).Data == 1 
      set(timesetmode_hnd, 'Visible', 'on')
  else
      set(timesetmode_hnd, 'Visible', 'off')
  end;

  if block.InputPort(5).Data == 2 
      set(alarmsetmode_hnd, 'Visible', 'on')
  else
      set(alarmsetmode_hnd, 'Visible', 'off')
  end;

  if block.InputPort(5).Data == 3 
      set(swatchmode_hnd, 'Visible', 'on')
  else
      set(swatchmode_hnd, 'Visible', 'off')
  end;
  
  if block.InputPort(6).Data == 1 
      set(alarm_hnd, 'Visible', 'on')
  else
      set(alarm_hnd, 'Visible', 'off')
  end;

 
%Update output ports

  block.OutputPort(1).Data = boolean(plusbutton);   % 8 for boolean, 0 for double, 3 for uint8 4 for int8
  block.OutputPort(2).Data = boolean(minusbutton);   % 8 for boolean, 0 for double, 3 for uint8 4 for int8
  block.OutputPort(3).Data = boolean(timebutton);   % 8 for boolean, 0 for double, 3 for uint8 4 for int8
  block.OutputPort(4).Data = boolean(timesetbutton);   % 8 for boolean, 0 for double, 3 for uint8 4 for int8
  block.OutputPort(5).Data = boolean(alarmbutton);   % 8 for boolean, 0 for double, 3 for uint8 4 for int8
  block.OutputPort(6).Data = boolean(swatchbutton);   % 8 for boolean, 0 for double, 3 for uint8 4 for int8
  block.OutputPort(7).Data = boolean(startbutton);   % 8 for boolean, 0 for double, 3 for uint8 4 for int8
  block.OutputPort(8).Data = boolean(stopbutton);   % 8 for boolean, 0 for double, 3 for uint8 4 for int8
%endfunction

