function zhubodisplay
    % ======================================================================
    % 功能：交互式演示一维驻波（由两个反向行波叠加形成）及其三维时空演化
    % 物理原理：
    %   右行波: y1 = A·sin(kx - ωt)
    %   左行波: y2 = A·sin(kx + ωt)
    %   驻波:   y = y1 + y2 = 2A·sin(kx)·cos(ωt)
    % ======================================================================

    % === 创建主窗口：一维驻波 GUI ===
    fig1D = figure('Position',[200, 200, 1000, 800], ...
        'Name','一维驻波演示（行波叠加）', ...
        'NumberTitle','off', 'MenuBar','none', 'ToolBar','none');
    
    % 左侧面板：参数控制区
    left_panel = uipanel(fig1D,'Title','驻波参数','FontSize',12,...
        'BackgroundColor',[0.96 0.96 0.96],'Position',[0.03 0.1 0.38 0.85]);
    
    % --- 振幅 A 控件 ---
    uicontrol(left_panel,'Style','text','String','振幅 A:','Position',[30,400,60,20]);
    sA = uicontrol(left_panel,'Style','slider','Min',0.1,'Max',3,'Value',1.5,...
        'Position',[100,400,150,20],'Callback',@updateSlider);
    eA = uicontrol(left_panel,'Style','edit','String','1.5','Position',[100,370,50,20],...
        'Callback',@updateEdit);
    
    % --- 波长 λ 控件 ---
    uicontrol(left_panel,'Style','text','String','波长 λ:','Position',[30,330,60,20]);
    sLam = uicontrol(left_panel,'Style','slider','Min',0.5,'Max',5,'Value',2.5,...
        'Position',[100,330,150,20],'Callback',@updateSlider);
    eLam = uicontrol(left_panel,'Style','edit','String','2.5','Position',[100,300,50,20],...
        'Callback',@updateEdit);
    
    % --- 频率 f 控件 ---
    uicontrol(left_panel,'Style','text','String','频率 f:','Position',[30,260,60,20]);
    sF = uicontrol(left_panel,'Style','slider','Min',0.1,'Max',2,'Value',1,...
        'Position',[100,260,150,20],'Callback',@updateSlider);
    eF = uicontrol(left_panel,'Style','edit','String','1','Position',[100,230,50,20],...
        'Callback',@updateEdit);
    
    % --- 右侧面板：一维波形绘图区 ---
    right_panel_1D = uipanel(fig1D,'Title','行波叠加形成驻波','FontSize',12,...
        'Position',[0.42 0.1 0.55 0.85]);
    ax1D = axes(right_panel_1D);
    hold(ax1D,'on');
    grid(ax1D,'on');
    xlabel(ax1D,'x (m)');
    ylabel(ax1D,'y');
    xlim(ax1D,[0 10]);          % 空间范围：0 到 10 米
    ylim(ax1D,[-3 3]);
    title(ax1D,'A=1.50, f=1.00 Hz, λ=2.50 m');
    legend(ax1D,'右行波','左行波','驻波','Location','northoutside','Orientation','horizontal');
    
    % 初始化三条曲线的图形句柄（用于高效更新，避免每帧重绘）
    x_plot = linspace(0, 10, 500);  % 高分辨率空间采样
    h_right = plot(ax1D, x_plot, nan(size(x_plot)), 'b', 'LineWidth',1.5);  % 右行波（蓝色）
    h_left  = plot(ax1D, x_plot, nan(size(x_plot)), 'r', 'LineWidth',1.5);  % 左行波（红色）
    h_total = plot(ax1D, x_plot, nan(size(x_plot)), 'k', 'LineWidth',2);    % 驻波（黑色加粗）
    
    % === 创建三维驻波展示窗口 ===
    fig3D = figure('Position',[1250, 250, 800, 600], ...
        'Name','三维空间内驻波展示', ...
        'NumberTitle','off', 'MenuBar','none', 'ToolBar','none');
    ax3D = axes(fig3D);
    view(ax3D, 30, 30);         % 默认视角
    xlabel(ax3D,'x (m)');
    ylabel(ax3D,'t (s)');       % 时间轴
    zlabel(ax3D,'Amplitude');
    title(ax3D,'三维驻波：空间(x) × 时间(t) 演化');
    shading(ax3D, 'interp');    % 平滑着色
    colorbar(ax3D);             % 显示颜色对应振幅
    rotate3d(ax3D, 'on');       % 允许用户用鼠标旋转3D视图
    
    % 定义空间网格（用于3D绘图）
    L = 10;                     % 空间长度（米）
    Nx = 300;                   % 空间采样点数（降低以提升性能）
    x = linspace(0, L, Nx);
    
    % === 启动动画定时器（约60 FPS）===
    % Period = 1/60 ≈ 0.0167 秒
    tmr = timer('ExecutionMode','fixedRate','Period',0.0167,...
        'TimerFcn',@(src,event) animate_both(ax1D, ax3D, x, sA, sLam, sF, h_right, h_left, h_total));
    start(tmr);
    
    % 👇 关键：立即执行一次动画，确保初始图形正确显示（避免空白）
    animate_both(ax1D, ax3D, x, sA, sLam, sF, h_right, h_left, h_total);
    
    % 设置窗口关闭回调，确保资源释放
    set(fig1D,'CloseRequestFcn',@closeAll);
    set(fig3D,'CloseRequestFcn',@closeAll);

    % ======================================================================
    % 辅助函数：编辑框输入 → 更新滑块
    % ======================================================================
    function updateEdit(src,event)
        val = str2double(get(src,'String'));
        if isnan(val), val = 1; end  % 输入非法时默认为1
        
        % 根据触发源确定对应的滑块
        slider = [];
        if src == eA,     slider = sA;
        elseif src == eLam, slider = sLam;
        elseif src == eF,   slider = sF;
        end
        
        if ~isempty(slider)
            minVal = get(slider,'Min');
            maxVal = get(slider,'Max');
            val = max(min(val, maxVal), minVal);  % 限制在滑块范围内
            set(slider,'Value',val);
            set(src,'String',num2str(val));       % 回写格式化值
        end
    end
    
    % ======================================================================
    % 辅助函数：滑块变动 → 更新编辑框
    % ======================================================================
    function updateSlider(src,event)
        val = get(src,'Value');
        if src == sA
            set(eA,'String',num2str(val));
        elseif src == sLam
            set(eLam,'String',num2str(val));
        elseif src == sF
            set(eF,'String',num2str(val));
        end
    end
    
    % ======================================================================
    % 核心动画函数：同时更新1D和3D图形
    % ======================================================================
    function animate_both(ax1D, ax3D, x, sA, sLam, sF, h_right, h_left, h_total)
        persistent t h_surf h_lines h_texts;  % 持久变量：时间 + 图形句柄
        if isempty(t)
            t = 0;
        end
        dt = 0.0167;  % 与定时器周期一致
        t = t + dt;
        
        % 获取当前用户设置的参数
        A = get(sA,'Value');
        lambda = get(sLam,'Value');
        f = max(get(sF,'Value'), 0.1);  % 防止频率为0导致除零
        
        % 计算波数 k 和角频率 ω
        k = 2*pi / lambda;
        w = 2*pi * f;
        
        % 更新1D图标题（显示当前参数）
        titleStr = sprintf('A=%.2f, f=%.2f Hz, λ=%.2f m', A, f, lambda);
        title(ax1D, titleStr);
        
        % ========== 一维驻波计算与更新 ==========
        x_plot = linspace(0, 10, 500);  % 与初始化一致
        y_right = A * sin(k*x_plot - w*t);   % 右行波
        y_left  = A * sin(k*x_plot + w*t);   % 左行波
        y_total = y_right + y_left;          % 驻波（叠加）
        
        % 高效更新曲线数据（不重绘整个图形）
        set(h_right, 'YData', y_right);
        set(h_left,  'YData', y_left);
        set(h_total, 'YData', y_total);
        ylim(ax1D, [-2.5*A 2.5*A]);  % 动态调整Y轴范围
        
        % ========== 三维驻波动画 ==========
        T_current = 1 / f;           % 当前周期
        Ny = 60;                     % 时间方向采样点数（降低以提升性能）
        ty = linspace(0, T_current, Ny);  % 一个完整周期的时间轴
        [X, TY] = meshgrid(x, ty);        % 构建 (x, t) 网格
        Y_standing = 2 * A * sin(k*X) .* cos(w*TY);  % 驻波解析式
        
        % 清除上一帧的3D图形（曲面、标注线、文本）
        try, delete(h_surf); catch, end; h_surf = [];
        try, delete(h_lines); catch, end; h_lines = [];
        try, delete(h_texts); catch, end; h_texts = [];
        
        % 绘制新的驻波曲面（无边线 + 插值着色）
        h_surf = surf(ax3D, X, TY, Y_standing, 'EdgeColor', 'none');
        shading(ax3D, 'interp');
        colormap(ax3D, jet);
        
        % 更新颜色条：自定义刻度标签（-2A, -A, 0, +A, +2A）
        c = colorbar(ax3D);
        c.Ticks = linspace(-2*A, 2*A, 5);
        c.TickLabels = {'-2A', '-A', '0', '+A', '+2A'};
        
        % 设置3D坐标轴标签
        title(ax3D, '三维驻波：空间(x) × 时间(t) 演化', 'FontSize', 12);
        xlabel(ax3D, 'x (m)');
        ylabel(ax3D, 't (s)');
        zlabel(ax3D, '位移 y');
        
        % ========== 标注波节（节点）与波腹（腹点）==========
        lambda_half = lambda / 2;
        x_nodes = 0 : lambda_half : 10;                % 波节位置：sin(kx)=0
        x_antinodes = lambda/4 : lambda_half : 10;     % 波腹位置：|sin(kx)|=1
        
        hold(ax3D, 'on');
        
        % 绘制波节（黑色虚线）
        for xn = x_nodes
            if xn <= 10
                h_lines(end+1) = plot3(ax3D, [xn xn], [min(ty) max(ty)], [0 0], 'k--', 'LineWidth', 1);
                h_texts(end+1) = text(ax3D, xn, min(ty), -0.3*A, sprintf('波节\n%.1f m', xn), ...
                    'FontSize', 7, 'Color', 'k', 'HorizontalAlignment', 'center');
            end
        end
        
        % 绘制波腹（红色实线）
        for xa = x_antinodes
            if xa <= 10
                h_lines(end+1) = plot3(ax3D, [xa xa], [min(ty) max(ty)], [0 0], 'r-', 'LineWidth', 1.5);
                h_texts(end+1) = text(ax3D, xa, min(ty), 2.2*A, sprintf('波腹\n%.1f m', xa), ...
                    'FontSize', 7, 'Color', 'r', 'HorizontalAlignment', 'center');
            end
        end
        
        % ========== 高亮当前时刻的波形切片 ==========
        current_t = mod(t, T_current);  % 当前时间对周期取模
        [~, idx] = min(abs(ty - current_t));  % 找到最接近的时间索引
        if ~isempty(idx) && idx <= length(ty)
            y_slice = Y_standing(idx, :);  % 提取该时刻的空间波形
            % 用黄色粗线绘制当前时刻的波形（连接1D与3D视图）
            h_lines(end+1) = plot3(ax3D, x, ty(idx)*ones(size(x)), y_slice, 'y', 'LineWidth', 3);
        end
        
        % ✅ 关键性能优化：限制图形刷新率，防止卡顿
        drawnow limitrate;
    end
    
    % ======================================================================
    % 窗口关闭回调：安全释放资源
    % ======================================================================
    function closeAll(~, ~)
        % 停止并删除定时器
        if exist('tmr', 'var') && ~isempty(tmr) && isvalid(tmr)
            stop(tmr);
            delete(tmr);
        end
        % 删除所有图形窗口
        if exist('fig1D', 'var') && ishandle(fig1D)
            delete(fig1D);
        end
        if exist('fig3D', 'var') && ishandle(fig3D)
            delete(fig3D);
        end
    end
end