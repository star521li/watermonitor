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

public class MfenxiFrm implements ActionListener {
	JFrame w;
	JDialog jdl=new JDialog(w,"水位分析查询",true);
	//显示信息的表
	String[] stafflistcols={"水位段","天数"};
	//设置表格整行显示
	DefaultTableModel model = new DefaultTableModel(null, stafflistcols);
	//数据显示表格
	JTable stafflist = new JTable(model);
	//滚动
    JScrollPane pane = new JScrollPane(stafflist);
	//查询模块
	JLabel ckclb = new JLabel("地区：");
	@SuppressWarnings("rawtypes")
	JComboBox ckctxt=new JComboBox(); 
	JLabel cktmlb = new JLabel("塔号：");
	@SuppressWarnings("rawtypes")
	JComboBox cktmtxt=new JComboBox(); 
	JButton checkbt = new JButton("查询");
	JLabel no=new JLabel("");
	JLabel ID = new JLabel("");
	@SuppressWarnings("unchecked")
	MfenxiFrm(JFrame jf){
		w=jf;
		jdl.setSize(900,280);		
		jdl.setLocation(200, 200);
		jdl.setLayout(null);
		jdl.setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);
		jdl.setResizable(false);
		//布局
		//查询部分布局
		jdl.add(ckclb);
		jdl.add(ckctxt);
		jdl.add(cktmlb);
		jdl.add(cktmtxt);
		jdl.add(checkbt);
		jdl.add(no);
		no.setBounds(0,0,0,0);
		ckclb.setBounds(230,10,50,20);
		ckctxt.setBounds(290,10,100,20);
		cktmlb.setBounds(400,10,50,20);
		cktmtxt.setBounds(450,10,100,20);
		checkbt.setBounds(600,10,60,20);
		//数据列表		
		jdl.add(pane);
		pane.setBounds(20,40,860,200);
		jdl.add(ID);
		ID.setBounds(0,0,0,0);
		ID.setVisible(false);
		checkbt.addActionListener(new CheckAction());
		DbHelper dh=new DbHelper();
		ckctxt.addItem("选择地区");
		ResultSet rs=dh.executeQuery("select  distinct place from shuita");
		try {
			while(rs.next()){
				ckctxt.addItem(rs.getString("place"));
			}
		} catch (SQLException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		ckctxt.setSelectedItem("选择塔号");
		cktmtxt.addItem("选择塔号");
		
		rs=dh.executeQuery("select distinct sname from shuita   ");
		try {
			while(rs.next()){
				cktmtxt.addItem(rs.getString("sname"));
			}
		} catch (SQLException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		cktmtxt.setSelectedItem("选择水塔");		
		
		stafflist.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		//数据列表添加鼠标监听
		stafflist.addMouseListener(new java.awt.event.MouseAdapter(){
            public void mouseClicked(MouseEvent e) {
            	//获取鼠标选中那一行的数据
              int r= stafflist.getSelectedRow();
              //获取每一列的值，赋值给右侧编辑区
              Object value= stafflist.getValueAt(r, 0);
              ID.setText(value.toString());
            }
        });
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
			
			if("选择地区".equals(ckctxt.getSelectedItem().toString())||"选择水塔".equals(cktmtxt.getSelectedItem().toString())){
				JOptionPane.showMessageDialog(null,"请选择地区和水塔", "系统信息", JOptionPane.ERROR_MESSAGE);	
				return;
			}			
			//获取数据，绑定到数据表
			getData();
		}
	}
	//获取查询结果，绑定到数据表
	public void getData(){
		Object cnm=0;
		Object tmm=0;			
		//如果查询有结果，则清空以往数据
		if(model.getRowCount()>0){
			for(int i=model.getRowCount()-1;i>=0;i--){
				model.removeRow(i);
			}
		}
		DbHelper db=new DbHelper();
		if(!"选择地区".equals(ckctxt.getSelectedItem().toString())){
			cnm=db.getOnlyOne("select sno from shuita where place='"+ckctxt.getSelectedItem()+"'");			
		}
		if(!"选择塔名".equals(cktmtxt.getSelectedItem().toString())){
			
			tmm=db.getOnlyOne("select sno from shuita where sname='"+cktmtxt.getSelectedItem()+"'");
		}
		String cksql="select '<20' as fsd,count(*) as rs from infor where shuiwei<20 and sno="+cnm+" and sno="+tmm+" "
				+ "union select '20-40'as fsd,count(*) as rs from infor where shuiwei between 20 and 40 and sno="+cnm+" and sno="+tmm+" "
						+ "union select '40-60'as fsd,count(*) as rs from infor where shuiwei between 40 and 60 and sno="+cnm+" and sno="+tmm+" "
								+ "union select '60-80'as fsd,count(*) as rs from infor where shuiwei between 60 and 80 and sno="+cnm+" and sno="+tmm+" "
										+ "union select '80-100'as fsd,count(*) as rs from infor where shuiwei between 80 and 100 and sno="+cnm+" and sno="+tmm +" "
										+ "union select '>100'as fsd,count(*) as rs from infor where shuiwei >100 and sno="+cnm+" and sno="+tmm ;
		ResultSet rs=db.executeQuery(cksql);
		if(rs!=null){
			try {
				while(rs.next()){
					model.addRow(new String[]{String.valueOf(rs.getString("fsd")),rs.getString("rs")});
				}
			} catch (SQLException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
		}
	}
	public void rst(){
		ID.setText("");
	}
//	public static void main(String[] arg){
//		new MckscoreFrm(new JFrame());
//	}
}
