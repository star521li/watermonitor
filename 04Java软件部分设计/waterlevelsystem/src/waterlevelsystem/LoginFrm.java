package waterlevelsystem;

import java.awt.Dimension;
import java.awt.Font;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPasswordField;
import javax.swing.JTextField;

public class LoginFrm implements ActionListener{
	
	private JFrame w = new JFrame("登录");//定义登录框
	private JLabel title = new JLabel("智能水位检测系统");
	private JLabel auther = new JLabel("毕设 电子141李思达");
	private JLabel username = new JLabel("用户名");//定义用户标签
	private JTextField usernamei = new JTextField("");//登录名输入框
	private JLabel password  = new JLabel("密码");//定义密码标签
	private JPasswordField passwordi = new JPasswordField();//登录密码输入框
	//private JLabel utype  = new JLabel("身份");//角色标签
	//private JComboBox  utypetxt =  new JComboBox<>();//登录选择角色下拉菜单
	private JButton dl = new JButton("登录");
	private JButton qx  = new JButton("重置");
	/**
	 * 构造的时候  初始化窗体
	 */
	public LoginFrm() {
		
		//设置窗体显示位置
		Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
		w.setLocation((dim.width - w.getWidth()) / 2-150, (dim.height - w.getHeight()) / 2-150);
		//设置窗体大小
		w.setSize(360, 280);
		/*// 把内容窗格转化为JPanel，否则不能用方法setOpaque()来使内容窗格透明  
		JPanel imagePanel = (JPanel) w.getContentPane();  
		imagePanel.setOpaque(false); */ 
		// 把背景图片添加到分层窗格的最底层作为背景  
		w.setLayout(null);
		//添加窗体关闭
		w.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		//设置控件位置
		title.setBounds(120, 25, 200, 20);
		title.setFont(new Font("",1,14));
		auther.setBounds(200, 217, 200, 20);
		auther.setFont(new Font("",1,14));
		username.setBounds(70, 70, 70, 20);
		usernamei.setBounds(150, 70, 120, 20);
		password.setBounds(70, 100, 70, 20);
		passwordi.setBounds(150, 100, 120, 20);
		//utype.setBounds(70, 130, 70, 20);
		//utypetxt.setBounds(150, 130, 120, 20);
		dl.setBounds(100, 180, 70, 25);
		qx.setBounds(180, 180, 70, 25);
		//控件添加到窗体
		w.add(auther);
		w.add(title);
		w.add(username);
		w.add(usernamei);
		w.add(password);
		w.add(passwordi);
		//w.add(utype);
		//w.add(utypetxt);
		w.add(dl);
		w.add(qx);
		//utypetxt.addItem("访问者");
		//utypetxt.addItem("管理员");
		w.setResizable(false);//窗体大小不可以变
		//添加监听器登录
		dl.addActionListener(new LoginSubmit());
		qx.addActionListener(new Reset());
		usernamei.setText("admin");
		passwordi.setText("admin");
		w.setVisible(true);
		
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
	}
	/**
	 *@ClassName LoginSubmit 
	 *@Description 用户登录操作监听 
	 */
	class LoginSubmit implements ActionListener{
		//boolean logflag=false;
		@Override
		public void actionPerformed(ActionEvent e) {	
			String uname=usernamei.getText().trim();
			String upassword=new String(passwordi.getPassword()).trim();//是去掉字符序列左边和右边的空格			
			DbHelper db=new DbHelper();
			String sql="select id from admin where uname='"+uname+"' and upassword='"+upassword+"'";
			/*if("管理员".equals(utypetxt.getSelectedItem().toString())){
				
			}else{
				sql="select id from students where sno='"+uname+"' and upassword='"+upassword+"'";
			}	*/		
			//登录，验证数据库账户信息
			Object uid=db.getOnlyOne(sql);//获取一行一列数据
			if(uid!=null){	
					new MainFrm(uid.toString());
				w.setVisible(false);
			}else{
				JOptionPane.showMessageDialog(null,"账户或密码错误!", "系统信息", JOptionPane.WARNING_MESSAGE);				
			}
		}
		
	}
	
	/**
	 *@ClassName Reset 
	 *@Description 重置监听
	 */
	class Reset implements ActionListener{

		@Override
		public void actionPerformed(ActionEvent e) {
			usernamei.setText("");
			passwordi.setText("");
			
		}
	}
	
	/**   
	 * @Title: main  
	 * @Description: 用户登录界面 主方法入口
	 *  @param args      
	 * @throws  
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		new LoginFrm();
	}
}


