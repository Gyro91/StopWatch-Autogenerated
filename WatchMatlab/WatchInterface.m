function WatchInterface(block)
% Level-2 M file S-Function for interface demo.
%   Copyright 1990-2004 The MathWorks, Inc.
%   $Revision: 1.1.6.1 $ 

  setup(block);
  
%endfunction

function setup(block)
  
  global timebutton
  global timesetbutton
  global alarmbutton
  global swatchbutton
  global plusbutton
  global minusbutton

  %% Register dialog parameters: No parameters for this block 
  block.NumDialogPrms = 0;
  
  %% Register number of input and output ports
  block.NumInputPorts  = 5;
  block.NumOutputPorts = 6;

  %% Setup functional port properties to dynamically
  %% inherited.
  block.SetPreCompInpPortInfoToDynamic;                    % port inherits sample rates
  block.SetPreCompOutPortInfoToDynamic;

  block.InputPort(1).Complexity   = 'Real'; 
  block.InputPort(1).DataTypeId   = 3;                     % 8 for boolean, 0 for double, 3 for uint8 4 for int8
  block.InputPort(1).SamplingMode = 'Sample';
  block.InputPort(1).Dimensions   = 10;
  block.InputPort(1).DirectFeedthrough   = 0;

  for i=2:5
    block.InputPort(i).Complexity   = 'Real'; 
    block.InputPort(i).DataTypeId   = 8;                     % 8 for boolean, 0 for double, 3 for uint8 4 for int8
    block.InputPort(i).SamplingMode = 'Sample';
    block.InputPort(i).Dimensions   = 1;
    block.InputPort(i).DirectFeedthrough   = 0;
  end;
  
  for i=1:6
    block.OutputPort(i).Complexity   = 'Real';
    block.OutputPort(i).DataTypeId   = 8;
    block.OutputPort(i).SamplingMode = 'Sample';
    block.OutputPort(i).Dimensions   = 1;
  end;

  %% Register methods
  block.RegBlockMethod('SetInputPortSamplingMode',@SetInputPortSamplingMode);
  block.RegBlockMethod('Start',                   @Start);  
  %   block.RegBlockMethod('WriteRTW',                @WriteRTW);
  block.RegBlockMethod('Outputs',                 @Outputs);
    
  timebutton=0;
  timesetbutton=0;
  alarmbutton=0;
  swatchbutton=0;
  plusbutton=0;
  minusbutton=0;
 
  %endfunction

 function SetInputPortSamplingMode(block, idx, fd)
   block.InputPort(idx).SamplingMode = fd;
%block.OutputPort(1).SamplingMode = fd;
%block.OutputPort(2).SamplingMode = fd;

function ButtonDown(hObj,evnt)
  global timebutton
  global timesetbutton
  global alarmbutton
  global swatchbutton
  global plusbutton
  global minusbutton

  pos = get(hObj,'CurrentPoint');
  if ((pos(2) > 240-(188+41)) && (pos(2) < 240-188) && (pos(1) > 25) && (pos(1) < (25+44)))
            timebutton=1;
  end;
  if ((pos(2) > 240-(188+41)) && (pos(2) < 240-188) && (pos(1) > 95) && (pos(1) < (95+42)))
            timesetbutton=1;
  end
  if ((pos(2) > 240-(188+41)) && (pos(2) < 240-188) && (pos(1) > 165) && (pos(1) < (165+42)))
            alarmbutton=1;
  end;
  if ((pos(2) > 240-(188+41)) && (pos(2) < 240-188) && (pos(1) > 242) && (pos(1) < (242+38)))
            swatchbutton=1;
  end;
  if ((pos(2) > 240-(28+36)) && (pos(2) < 240-28) && (pos(1) > 256) && (pos(1) < (256+36)))
            plusbutton=1;
  end;
  if ((pos(2) > 240-(100+36)) && (pos(2) < 240-100) && (pos(1) > 256) && (pos(1) < (256+36)))
            minusbutton=1;
  end;

  
function ButtonUp(hObj,evnt)
  global timebutton
  global timesetbutton
  global alarmbutton
  global swatchbutton
  global plusbutton
  global minusbutton

  pos = get(hObj,'CurrentPoint');
  if ((pos(2) > 240-(188+41)) && (pos(2) < 240-188) && (pos(1) > 25) && (pos(1) < (25+44)))
            timebutton=0;
  end;
  if ((pos(2) > 240-(188+41)) && (pos(2) < 240-188) && (pos(1) > 95) && (pos(1) < (95+42)))
            timesetbutton=0;
  end;
  if ((pos(2) > 240-(188+41)) && (pos(2) < 240-188) && (pos(1) > 165) && (pos(1) < (165+42)))
            alarmbutton=0;
  end;
  if ((pos(2) > 240-(188+41)) && (pos(2) < 240-188) && (pos(1) > 242) && (pos(1) < (242+38)))
            swatchbutton=0;
  end;
  if ((pos(2) > 240-(28+36)) && (pos(2) < 240-28) && (pos(1) > 256) && (pos(1) < (256+36)))
            plusbutton=0;
  end;
  if ((pos(2) > 240-(100+36)) && (pos(2) < 240-100) && (pos(1) > 256) && (pos(1) < (256+36)))
            minusbutton=0;
  end;


function Start(block)  
  global IM
  global IM1
  global imh1
  global IM2
  global imh2
  global IM3
  global imh3
  global IM4
  global imh4
  global FH
  global th1
  
  IM = imread('images\sfondo.png');
  IM1 = imread('images\timeON.png'); %% , 'BackgroundColor', [134/256 255/256 124/256]);
  IM2 = imread('images\timesetON.png'); %% , 'BackgroundColor', [134/256 255/256 124/256]);
  IM3 = imread('images\alarmON.png'); %% , 'BackgroundColor', [134/256 255/256 124/256]);
  IM4 = imread('images\swatchON.png'); %% , 'BackgroundColor', [134/256 255/256 124/256]);

%%  IM1 = imread('IMG\resistor.png', 'BackgroundColor', [134/256 255/256 124/256]);
  %% Initialize Dwork 
  bhD = @ButtonDown;
  bhU = @ButtonUp;
  FH = figure('Toolbar', 'none', 'Menubar', 'none', 'Name', 'Figname', 'WindowButtonDownFcn', bhD, 'WindowButtonUpFcn', bhU, 'Resize', 'off');
  scrsz = get(0,'ScreenSize');
  set(FH, 'Units','pixels')
  set(FH, 'Position',[1 scrsz(4)-500 320 240])
  hax = axes('Units', 'pixels', 'Position', [1, 1, 320, 240], 'Visible', 'off');
  image(IM)
  axis off

%  hax = axes('Units', 'pixels', 'Position', [247, 472-211, 660*factor, 393*factor], 'Visible', 'off')
%  axis off
  th1 = text(33, 240-69,'', 'Units', 'pixels', 'FontUnits', 'points', 'FontSize', 24);
  set(th1, 'Color',[1 1 1]);
  set(th1, 'VerticalAlignment','top');
  set(th1, 'FontName', 'Arial');

  hax = axes('Units', 'pixels', 'Position', [30, 240-188-43, 39, 43], 'Visible', 'off');
  imh1 = image(IM1, 'Visible', 'off');
  axis off;
  hax = axes('Units', 'pixels', 'Position', [98, 240-188-43, 39, 43], 'Visible', 'off');
  imh2 = image(IM2, 'Visible', 'off');
  axis off;
  hax = axes('Units', 'pixels', 'Position', [169, 240-188-43, 38, 43], 'Visible', 'off');
  imh3 = image(IM3, 'Visible', 'off');
  axis off;
  hax = axes('Units', 'pixels', 'Position', [244, 240-188-43, 35, 43], 'Visible', 'off');
  imh4 = image(IM4, 'Visible', 'off');
  axis off;

  % set(FH, 'CurrentAxes', base_axes)



 % th = text(1, 120,'', 'FontUnits', 'pixels', 'FontSize', 200)
 % set(th, 'FontName', '7 Segment')
 % set(th, 'string', '000')

% ti_tronic_gui('ti_tronic_gui_RegisterBlock', [0], [block], []);  
%endfunction
  
function Outputs(block)
  
  global timebutton
  global timesetbutton
  global alarmbutton
  global swatchbutton
  global plusbutton
  global minusbutton
  global th1
  global imh1
  global imh2
  global imh3
  global imh4
 % 
  % set(FH, 'CurrentAxes', h1)

  set(th1, 'string', char(block.InputPort(1).Data'))

  if block.InputPort(2).Data == 1 
      set(imh1, 'Visible', 'on')
  else
      set(imh1, 'Visible', 'off')
  end;
  if block.InputPort(3).Data == 1 
      set(imh2, 'Visible', 'on')
  else
      set(imh2, 'Visible', 'off')
  end;
  if block.InputPort(4).Data == 1 
      set(imh3, 'Visible', 'on')
  else
      set(imh3, 'Visible', 'off')
  end;
  if block.InputPort(5).Data == 1 
      set(imh4, 'Visible', 'on')
  else
      set(imh4, 'Visible', 'off')
  end;

  block.OutputPort(1).Data = boolean(timebutton);
  block.OutputPort(2).Data = boolean(timesetbutton);
  block.OutputPort(3).Data = boolean(alarmbutton);
  block.OutputPort(4).Data = boolean(swatchbutton);
  block.OutputPort(5).Data = boolean(plusbutton);
  block.OutputPort(6).Data = boolean(minusbutton);
  % X = block.Dwork(1).Data;
  % H = block.Dwork(2).Data;  
  % block.Dwork(1).Data = X;
  % block.Dwork(2).Data = H;
  

  %% Outputs the difference between the estimated filter coefficients
  %% and the actual coefficients.
  
%endfunction


