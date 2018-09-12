using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SQLite;
using System.Linq;
using System.Text;

namespace S32PSave
{
    public class SqlLite
    {
       
            private static readonly string connStr ="Data Source=data\\local.db;";
        

            /// <summary>
            /// 执行增删改的方法
            /// </summary>
            /// <param name="sql"></param>
            /// <param name="pms"></param>
            /// <returns></returns>
            public static int ExecuteNonQuery(string sql, params SQLiteParameter[] pms)
            {
                using (SQLiteConnection con = new SQLiteConnection(connStr))
                {
                    using (SQLiteCommand cmd = new SQLiteCommand(sql, con))
                    {
                        if (pms != null)
                        {
                            cmd.Parameters.AddRange(pms);
                        }
                        con.Open();
                        return cmd.ExecuteNonQuery();
                    }
                }
            }


            /// <summary>
            /// 执行返回单个值的方法
            /// </summary>
            /// <param name="sql"></param>
            /// <param name="pms"></param>
            /// <returns></returns>
            public static object ExecuteScalar(string sql, params SQLiteParameter[] pms)
            {
                using (SQLiteConnection con = new SQLiteConnection(connStr))
                {
                    using (SQLiteCommand cmd = new SQLiteCommand(sql, con))
                    {
                        if (pms != null)
                        {
                            cmd.Parameters.AddRange(pms);
                        }
                        con.Open();
                        return cmd.ExecuteScalar();
                    }
                }
            }

            /// <summary>
            /// 执行返回reader的方法
            /// </summary>
            /// <param name="sql"></param>
            /// <param name="pms"></param>
            /// <returns></returns>
            public static SQLiteDataReader ExecuteReader(string sql, params SQLiteParameter[] pms)
            {
                SQLiteConnection con = new SQLiteConnection(connStr);
                using (SQLiteCommand cmd = new SQLiteCommand(sql, con))
                {
                    if (pms != null)
                    {
                        cmd.Parameters.AddRange(pms);
                    }
                    try
                    {
                        con.Open();
                        return cmd.ExecuteReader(System.Data.CommandBehavior.CloseConnection);
                        //System.Data.CommandBehavior.CloseConnection,表示DataReader对象调用结束后，释放conn
                    }
                    catch
                    {
                        con.Close();
                        con.Dispose();
                        throw;
                    }
                }
            }

            /// <summary>
            /// 执行返回一个DataTable的方法
            /// </summary>
            /// <param name="sql"></param>
            /// <param name="pms"></param>
            /// <returns></returns>
            public static DataTable ExecuteDataTable(string sql, params SQLiteParameter[] pms)
            {
                DataTable dt = new DataTable();
                using (SQLiteDataAdapter adapter = new SQLiteDataAdapter(sql, connStr))
                {
                    if (pms != null)
                    {
                        adapter.SelectCommand.Parameters.AddRange(pms);
                    }
                    adapter.Fill(dt);
                }
                return dt;
            }
        }
   
}
