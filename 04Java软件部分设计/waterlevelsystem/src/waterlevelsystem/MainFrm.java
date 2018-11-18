package waterlevelsystem;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;

public class MainFrm implements ActionListener {	
	public  static String uid;
	public  JFrame w = new JFrame("水位检测信息管理系统");//窗体
	private JMenuBar mb=new JMenuBar();//菜单栏
	private JMenu sysmanage = new JMenu("系统管理");//菜单
	private JMenuItem madmin=new JMenuItem("管理员信息");//菜单项
	private JMenuItem backlogin=new JMenuItem("返回登陆");
	
	private JMenu jbxxgl=new JMenu("水位塔水位管理");	
	private JMenuItem mterm=new JMenuItem("水塔信息管理");
	private JMenuItem mcourse=new JMenuItem("水位信息管理");	
	
	private JMenu wxgl=new JMenu("水位信息分析");
	private JMenuItem mstudent=new JMenuItem("水位信息分析");
	//构成初始化界面
	MainFrm(String u){
		uid=u;
		w.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();  
		w.setLocation((dim.width - w.getWidth()) / 2-150, (dim.height - w.getHeight()) / 2-150);  				
		w.setSize(600, 500);
		w.setResizable(false);
		// 把内容窗格转化为JPanel面板容器，否则不能用方法setOpaque()来使内容窗格透明  
		JPanel imagePanel = (JPanel) w.getContentPane();  
		imagePanel.setOpaque(false);  
		sysmanage.add(madmin);
		sysmanage.add(backlogin);		
		jbxxgl.add(mterm);
		jbxxgl.add(mcourse);
		wxgl.add(mstudent);
		mb.add(sysmanage);
		mb.add(jbxxgl);
		mb.add(wxgl);
		//mb.add(tsgl);
		w.add(mb,BorderLayout.NORTH);
		//设置背景
		String path= "1.jpg";
		ImageIcon bg=new ImageIcon(path);
		JLabel bglb=new JLabel(bg);
		bglb.setBounds(0, 0, w.getWidth(), w.getHeight());
		JPanel imgpanel=(JPanel)w.getContentPane();
		imgpanel.setOpaque(false);
		w.getLayeredPane().add(bglb, new Integer(Integer.MIN_VALUE));
		//给菜单添加监听
		madmin.addActionListener(new madmin());
		backlogin.addActionListener(new backlog());		
		mcourse.addActionListener(new mcourse());
		mterm.addActionListener(new mterm());
		mstudent.addActionListener(new mstudent());
		w.setLocation(200, 200);
		w.setVisible(true);
	}
	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub

	}
	//管理员信息管理
	class madmin implements ActionListener{
		@Override
		public void actionPerformed(ActionEvent e) {
			// TODO Auto-generated method stub
			new MadminFrm(w);
		}
	}
	//水位信息管理
	class mcourse implements ActionListener{
		@Override
		public void actionPerformed(ActionEvent e) {
			// TODO Auto-generated method stub
			new MshuiweiFrm(w);
		}
	}
	//水塔信息管理
	class mterm implements ActionListener{
		@Override
		public void actionPerformed(ActionEvent e) {
			// TODO Auto-generated method stub
			new MshuitaFrm(w);
		}
	}

	//水位分析
	class mstudent implements ActionListener{
		@Override
		public void actionPerformed(ActionEvent e) {
			// TODO Auto-generated method stub
			new MfenxiFrm(w);
		}
	}

	//系统注销
	class backlog implements ActionListener{
		@Override
		public void actionPerformed(ActionEvent e) {
			// TODO Auto-generated method stub
			w.dispose();
			new LoginFrm();
		}
	}
}