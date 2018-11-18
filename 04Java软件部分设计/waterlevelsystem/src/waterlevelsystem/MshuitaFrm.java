package waterlevelsystem;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.sql.ResultSet;
import java.sql.SQLException;

import javax.swing.BorderFactory;
import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.ListSelectionModel;
import javax.swing.table.DefaultTableModel;

public class MshuitaFrm implements ActionListener {
	String cksql="select shuita.* from shuita where 1 = 1";
	JFrame w;
	JDialog jdl=new JDialog(w,"水塔信息管理",true);
	//显示信息的表
	String[] stafflistcols={"id","塔号","塔名","地区"};
	//设置表格整行显示
	DefaultTableModel model = new DefaultTableModel(null, stafflistcols);
	//数据显示表格
	JTable stafflist = new JTable(model);
	//滚动
    JScrollPane pane = new JScrollPane(stafflist);
	//查询模块
	JLabel cksnolb = new JLabel("塔号：");
	JTextField cksnotxt=new JTextField();
	JLabel ckclsslb = new JLabel("塔名：");
	JTextField ckclsstxt=new JTextField(); 
	JButton checkbt = new JButton("查询");
	JLabel no=new JLabel("");
	//管理模块
	JLabel mgsnolb=new JLabel("塔号：");
	JTextField mgsnotxt=new JTextField();
	JLabel mgsnamelb=new JLabel("塔名：");
	JTextField mgsnametxt=new JTextField();
	
	

	JLabel mgclsslb=new JLabel("地区：");
	JTextField mgclsstxt=new JTextField();
	JLabel ID = new JLabel("");
	JPanel jpl=new JPanel(new BorderLayout());
	JButton addbt = new JButton("添加");
	JButton updbt = new JButton("修改");
	JButton delbt = new JButton("删除");
	JButton resbt = new JButton("重置");
	@SuppressWarnings("unchecked")
	MshuitaFrm(JFrame jf){
		w=jf;
		jdl.setSize(800,400);		
		jdl.setLocation(200, 200);
		jdl.setLayout(null);
		jdl.setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);
		jdl.setResizable(false);
		//布局
		//查询部分布局
		jdl.add(cksnolb);
		jdl.add(cksnotxt);
		jdl.add(ckclsslb);
		jdl.add(ckclsstxt);
		jdl.add(checkbt);
		jdl.add(no);
		no.setBounds(0,0,0,0);
		cksnolb.setBounds(60,10,70,20);
		cksnotxt.setBounds(135,10,100,20);
		ckclsslb.setBounds(250,10,70,20);
		ckclsstxt.setBounds(330,10,100,20);
		checkbt.setBounds(440,10,60,20);
		//数据列表		
		jdl.add(pane);
		pane.setBounds(20,40,760,200);
		jpl.setBounds(20, 250, 760, 120) ;
		jdl.add(jpl);
		jpl.setBorder(BorderFactory.createTitledBorder("编辑区"));
		jpl.setOpaque(false);
		//数据管理部分布局
		jpl.add(mgsnolb);
		mgsnolb.setBounds(20, 30, 50, 20);
		jpl.add(mgsnotxt);
		mgsnotxt.setBounds(80, 30, 100, 20);
		jpl.add(mgsnamelb);
		mgsnamelb.setBounds(190, 30, 50, 20);
		jpl.add(mgsnametxt);
		mgsnametxt.setBounds(250, 30, 100, 20);
	
		jpl.add(mgclsslb);
		mgclsslb.setBounds(490, 30, 50, 20);
		jpl.add(mgclsstxt);
		mgclsstxt.setBounds(550, 30, 120, 20);
		jpl.add(addbt);
		addbt.setBounds(150, 60, 60, 20);
		jpl.add(updbt);
		updbt.setBounds(230, 60, 60, 20);
		jpl.add(delbt);
		delbt.setBounds(310, 60, 60, 20);
		jpl.add(resbt);
		resbt.setBounds(390, 60, 60, 20);
		jpl.add(ID);
		ID.setBounds(0,0,0,0);
		ID.setVisible(false);
		checkbt.addActionListener(new CheckAction());
		DbHelper dh=new DbHelper();
		

		stafflist.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		//数据列表添加鼠标监听
		stafflist.addMouseListener(new java.awt.event.MouseAdapter(){
            public void mouseClicked(MouseEvent e) {
            	//获取鼠标选中那一行的数据
              int r= stafflist.getSelectedRow();
              //获取每一列的值，赋值给右侧编辑区
              Object value= stafflist.getValueAt(r, 0);
              ID.setText(value.toString());
              mgsnotxt.setText(stafflist.getValueAt(r, 1).toString());
              mgsnametxt.setText(stafflist.getValueAt(r, 2).toString());
              mgclsstxt.setText(stafflist.getValueAt(r, 3).toString());
            }
        });
		//为增删改重置功能添加监听事件
		addbt.addActionListener(new AddAction());
		updbt.addActionListener(new UpdAction());
		delbt.addActionListener(new DelAction());
		resbt.addActionListener(new ResAction());
		getData(cksql);
		
		jdl.setVisible(true);
	}
	@Override
	public void actionPerformed(ActionEvent e) {
	}
	//查询功能实现
	class CheckAction implements ActionListener{		
		ResultSet rs=null;		
		@Override
		public void actionPerformed(ActionEvent e) {
			// TODO Auto-generated method coub			
			//获取数据，绑定到数据表
			getData(cksql);
		}
	}
	//添加功能实现
	class AddAction implements ActionListener{
		String sql="";
		ResultSet rs=null;
		@Override
		public void actionPerformed(ActionEvent e) {
			// TODO Auto-generated method coub
			String sno=mgsnotxt.getText().trim();
			String sname=mgsnametxt.getText().trim();
			
			String clssname=mgclsstxt.getText().toString().trim();
			if("".equals(sno)||"".equals(sname)||"".equals(clssname)){
				JOptionPane.showMessageDialog(null,"水塔信息不完整!", "系统信息", JOptionPane.WARNING_MESSAGE);	
				return;
			}
			DbHelper db=new DbHelper();
			if(db.checkTrue("select id from shuita where sno='"+sno+"'")){
				JOptionPane.showMessageDialog(null,"塔号已存在!", "系统信息", JOptionPane.WARNING_MESSAGE);	
				return;
			}
			int x=db.executeUpdate("insert into shuita(sno,sname,place) values('"+sno+"','"+sname+"','"+clssname+"')");
			if(x>0){
				JOptionPane.showMessageDialog(null,"添加成功.", "系统信息", JOptionPane.INFORMATION_MESSAGE);	
			}else{
				JOptionPane.showMessageDialog(null,"系统错误01", "系统信息", JOptionPane.ERROR_MESSAGE);	
			}
			//获取数据，绑定到数据表
			getData(cksql);
			//重置
			rst();
		}
	}
	//重置功能实现
	class ResAction implements ActionListener{
		@Override
		public void actionPerformed(ActionEvent e) {
			// TODO Auto-generated method coub
			rst();
		}
	}
	//删除功能实现
	class DelAction implements ActionListener{
		ResultSet rs=null;	
		@Override
		public void actionPerformed(ActionEvent e) {
			// TODO Auto-generated method coub
			String id=ID.getText();
			DbHelper db=new DbHelper();
			if("".equals(id)||!db.checkTrue("select id from shuita where id="+id)){
				JOptionPane.showMessageDialog(null,"请选择所要删除的信息!", "系统信息", JOptionPane.WARNING_MESSAGE);	
				return;
			}			
			int x=db.executeUpdate("delete from shuita where id="+id);
			if(x>0){
				JOptionPane.showMessageDialog(null,"删除成功.", "系统信息", JOptionPane.INFORMATION_MESSAGE);	
				//获取数据，绑定到数据表
				getData(cksql);
				//重置
				rst();
			}else{
				JOptionPane.showMessageDialog(null,"系统错误01", "系统信息", JOptionPane.ERROR_MESSAGE);	
			}			
		}
	}
	//修改功能实现
	class UpdAction implements ActionListener{
		ResultSet rs=null;	
		@Override
		public void actionPerformed(ActionEvent e) {
			// TODO Auto-generated method coub
			String id=ID.getText();
			if("".equals(id)){
				JOptionPane.showMessageDialog(null,"请选择所要修改的信息!", "系统信息", JOptionPane.WARNING_MESSAGE);	
				return;
			}
			String sno=mgsnotxt.getText().trim();
			String sname=mgsnametxt.getText().trim();
			
			String clssname=mgclsstxt.getText().toString().trim();
			if("".equals(sno)||"".equals(sname)||"".equals(clssname)){
				JOptionPane.showMessageDialog(null,"水塔信息不完整!", "系统信息", JOptionPane.WARNING_MESSAGE);	
				return;
			}
			DbHelper db=new DbHelper();
			rs=db.executeQuery("select id from shuita where place='"+sno+"'");
			try {
				while(rs.next()){
					String idi=String.valueOf(rs.getInt("id"));
					if(!id.equals(idi)){
						JOptionPane.showMessageDialog(null,"塔号已存在!", "系统信息", JOptionPane.WARNING_MESSAGE);	
						return;
					}
				}
			} catch (SQLException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			int x=db.executeUpdate("update place set sno='"+sno+"',sname='"+sname+"',place='"+clssname+"' where id="+id);
			if(x>0){
				JOptionPane.showMessageDialog(null,"修改成功.", "系统信息", JOptionPane.INFORMATION_MESSAGE);	
				//获取数据，绑定到数据表
				getData(cksql);
				//重置
				rst();
			}else{
				JOptionPane.showMessageDialog(null,"系统错误01", "系统信息", JOptionPane.ERROR_MESSAGE);	
			}
		}
	}
	//获取查询结果，绑定到数据表
	public void getData(String sql){
		//如果查询有结果，则清空以往数据
		if(model.getRowCount()>0){
			for(int i=model.getRowCount()-1;i>=0;i--){
				model.removeRow(i);
			}
		}
		DbHelper db=new DbHelper();
		if(!"".equals(ckclsstxt.getText().toString())){
			sql+=" and sname like '%"+ckclsstxt.getText()+"%'";
		}
		if(!"".equals(cksnotxt.getText())){
			sql+=" and sno='"+cksnotxt.getText()+"'";
		}
		ResultSet rs=db.executeQuery(sql);
		if(rs!=null){
			try {
				while(rs.next()){
					model.addRow(new String[]{String.valueOf(rs.getInt("ID")),rs.getString("sno"),rs.getString("sname"),rs.getString("place")});
				}
			} catch (SQLException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
		}
	}
	public void rst(){
		ID.setText("");
		mgsnotxt.setText("");
		mgsnametxt.setText("");
		mgclsstxt.setText("");
	}
}
